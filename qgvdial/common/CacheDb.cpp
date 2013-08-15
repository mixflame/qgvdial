/*
qgvdial is a cross platform Google Voice Dialer
Copyright (C) 2009-2013  Yuvraaj Kelkar

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

Contact: yuvraaj@gmail.com
*/

#include "CacheDb.h"
#include "CacheDb_p.h"
#include "Lib.h"

CacheDb::CacheDb(QObject *parent /* = NULL*/)
: QObject (parent)
{
}//CacheDb::CacheDb

CacheDb::~CacheDb()
{
}//CacheDb::~CacheDb

bool
CacheDb::init(const QString &dbDir)
{
    if (!dbDir.isEmpty ()) {
        CacheDbPrivate::setDbDir (dbDir);
    }

    CacheDbPrivate &p = CacheDbPrivate::ref ();

    bool bBlowAway = true;
    QString strVer = p.settings->value(GV_S_VAR_DB_VER).toString();
    if (strVer == GV_S_VALUE_DB_VER) {
        // Ensure that the version matches what we have hardcoded into this
        // binary. If not drop all cache tables.
        bBlowAway = false;
    }
    strVer = p.settings->value(GV_S_VAR_VER).toString();
    if (strVer != GV_SETTINGS_VER) {
        // If the settings change, EVERYTHING GOES!
        bBlowAway = true;
        // Clear out all settings as well
        p.settings->clear ();
        p.settings->setValue (GV_S_VAR_VER, GV_SETTINGS_VER);
    }
    if (bBlowAway) {
        if (!blowAwayCache ()) {
            Q_WARN("Failed to blow away cache");
            exit(1);
            return (false);
        }

        // Insert the DB version number
        p.settings->setValue(GV_S_VAR_DB_VER, GV_S_VALUE_DB_VER);
    }

    ensureCache ();
    return (true);
}//CacheDb::init

void
CacheDb::deinit()
{
    CacheDbPrivate::deref ();
}//CacheDb::deinit


bool
CacheDb::blowAwayCache()
{
    CacheDbPrivate &p = CacheDbPrivate::ref ();
    QString name = p.db.databaseName ();
    p.db.close ();
    QFile::remove(name);
    if (!p.db.open ()) {
        Q_WARN(QString("Failed to open database %1. Error text = %2")
                .arg(name, p.db.lastError().text()));
        qApp->quit ();
        return (false);
    }

    //TODO: Re-enable this
    //deleteTempDirectory ();

    return (true);
}//CacheDb::blowAwayCache

void
CacheDb::ensureCache ()
{
    CacheDbPrivate &p = CacheDbPrivate::ref ();
    QSqlQuery query(p.db);
    query.setForwardOnly (true);

    QStringList arrTables = p.db.tables ();
    // Ensure that the contacts table is present. If not, create it.
    if (!arrTables.contains (GV_CONTACTS_TABLE)) {
        query.exec ("CREATE TABLE " GV_CONTACTS_TABLE " "
                    "(" GV_C_NAME    " varchar, "
                        GV_C_ID      " varchar, "
                        GV_C_NOTES   " varchar, "
                        GV_C_PICLINK " varchar, "
                        GV_C_UPDATED " integer)");
    }

    // Ensure that the cached links table is present. If not, create it.
    if (!arrTables.contains (GV_LINKS_TABLE)) {
        query.exec ("CREATE TABLE " GV_LINKS_TABLE " "
                    "(" GV_L_LINK   " varchar, "
                        GV_L_TYPE   " varchar, "
                        GV_L_DATA   " varchar)");
    }

    // Ensure that the registered numbers table is present. If not, create it.
    if (!arrTables.contains (GV_REG_NUMS_TABLE)) {
        query.exec ("CREATE TABLE " GV_REG_NUMS_TABLE " "
                    "(" GV_RN_NAME           " varchar, "
                        GV_RN_NUM            " varchar, "
                        GV_RN_TYPE           " tinyint, "
                        GV_RN_FLAGS          " integer, "
                        GV_RN_FWDCOUNTRY     " varchar, "
                        GV_RN_DISPUNVERIFYDT " varchar"
                    ")");
    }

    // Ensure that the call initiators table is present. If not, create it.
    if (!arrTables.contains (GV_CI_TABLE)) {
        query.exec ("CREATE TABLE " GV_CI_TABLE " "
                    "(" GV_CI_ID     " varchar, "
                        GV_CI_NUMBER " varchar"
                    ")");
    }

    // Ensure that the inbox table is present. If not, create it.
    if (!arrTables.contains (GV_INBOX_TABLE)) {
        query.exec ("CREATE TABLE " GV_INBOX_TABLE " "
                    "(" GV_IN_ID        " varchar, "
                        GV_IN_TYPE      " tinyint, "
                        GV_IN_ATTIME    " bigint, "
                        GV_IN_DISPNUM   " varchar, "
                        GV_IN_PHONE     " varchar, "
                        GV_IN_FLAGS     " integer, "
                        GV_IN_SMSTEXT   " varchar, "
                        GV_IN_NOTE      " varchar)");
    }

    // Ensure that the temp file table is present. If not, create it.
    if (!arrTables.contains (GV_TEMP_TABLE)) {
        query.exec ("CREATE TABLE " GV_TEMP_TABLE " "
                    "(" GV_TT_CTIME " varchar, "
                        GV_TT_LINK  " varchar, "
                        GV_TT_PATH  " varchar)");
    }

    // Ensure that the cookie jar is present. If not, create it.
    if (!arrTables.contains (GV_COOKIEJAR_TABLE)) {
        query.exec ("CREATE TABLE " GV_COOKIEJAR_TABLE " "
                    "(" GV_CJ_DOMAIN        " varchar, "
                        GV_CJ_EXPIRATION    " varchar, "
                        GV_CJ_HTTP_ONLY     " integer, "
                        GV_CJ_IS_SECURE     " integer, "
                        GV_CJ_IS_SESSION    " integer, "
                        GV_CJ_NAME          " varchar, "
                        GV_CJ_PATH          " varchar, "
                        GV_CJ_VALUE         " varchar)");
    }

    query.exec ("VACUUM");
}//CacheDb::ensureCache

bool
CacheDb::usernameIsCached()
{
    return CacheDbPrivate::ref().settings->contains (GV_S_VAR_USER);
}//CacheDb::usernameIsCached

bool
CacheDb::getUserPass (QString &strUser, QString &strPass)
{
    QByteArray byD;
    Lib &lib = Lib::ref();
    QString strResult;
    CacheDbPrivate &p = CacheDbPrivate::ref();
    bool bGotUser = false;

    if (p.settings->contains (GV_S_VAR_USER)) {
        strResult = p.settings->value(GV_S_VAR_USER).toString();
        lib.cipher (QByteArray::fromHex (strResult.toAscii ()), byD, false);
        strUser = byD;
        bGotUser = true;
    }

    if (p.settings->contains (GV_S_VAR_PASS)) {
        strResult = p.settings->value(GV_S_VAR_PASS).toString();
        if (!bGotUser) {
            p.settings->remove (GV_S_VAR_PASS);
        } else {
            lib.cipher (QByteArray::fromHex (strResult.toAscii ()), byD, false);
            strPass = byD;
        }
    }

    return (bGotUser);
}//CacheDb::getUserPass

bool
CacheDb::putUserPass (const QString &strUser, const QString &strPass)
{
    QByteArray byD;
    Lib &lib = Lib::ref();
    CacheDbPrivate &p = CacheDbPrivate::ref();

    lib.cipher (strUser.toAscii (), byD, true);
    p.settings->setValue (GV_S_VAR_USER, QString (byD.toHex ()));

    lib.cipher (strPass.toAscii (), byD, true);
    p.settings->setValue (GV_S_VAR_PASS, QString (byD.toHex ()));

    return (true);
}//CacheDb::petUserPass

bool
CacheDb::clearUserPass()
{
    CacheDbPrivate &p = CacheDbPrivate::ref();
    p.settings->remove (GV_S_VAR_USER);
    p.settings->remove (GV_S_VAR_PASS);
}//CacheDb::clearUserPass

bool
CacheDb::saveCookies(QList<QNetworkCookie> cookies)
{
    CacheDbPrivate &p = CacheDbPrivate::ref ();
    QSqlQuery query(p.db);
    query.setForwardOnly (true);

    query.exec ("DELETE FROM " GV_COOKIEJAR_TABLE);

    QString strQ, domain, path;
    bool isHttpOnly, isSecure, isSession;
    QByteArray name, value;
    quint32 expiration;
    bool rv;

    foreach(QNetworkCookie cookie, cookies) {
        domain = cookie.domain ();
        path = cookie.path ();
        isHttpOnly = cookie.isHttpOnly ();
        isSecure = cookie.isSecure ();
        isSession = cookie.isSessionCookie ();
        name = cookie.name ();
        value = cookie.value ();
        expiration = cookie.expirationDate().toTime_t ();

        domain.replace ("'", "''");
        path.replace ("'", "''");

        strQ = QString ("INSERT INTO " GV_COOKIEJAR_TABLE " ("
                        GV_CJ_DOMAIN ","        // 1
                        GV_CJ_EXPIRATION ","    // 2
                        GV_CJ_HTTP_ONLY ","     // 3
                        GV_CJ_IS_SECURE ","     // 4
                        GV_CJ_IS_SESSION ","    // 5
                        GV_CJ_NAME ","          // 6
                        GV_CJ_PATH ","          // 7
                        GV_CJ_VALUE ") "        // 8
                        "VALUES ('%1', %2, %3, %4, %5, :name, '%6', :value)")
                .arg (domain)
                .arg (expiration)
                .arg (isHttpOnly ? 1 : 0)
                .arg (isSecure ? 1 : 0)
                .arg (isSession ? 1 : 0)
                .arg (path);
        rv = query.prepare (strQ);
        Q_ASSERT(rv);
        query.bindValue (":name", name);
        query.bindValue (":value", value);
        rv = query.exec ();
        if (!rv) {
            Q_WARN(QString("Failed to insert cookie into DB. %1")
                   .arg(query.lastError().text()));
            Q_ASSERT(rv);
        }
    }

    return (true);
}//CacheDb::saveCookies

bool
CacheDb::loadCookies(QList<QNetworkCookie> &cookies)
{
    CacheDbPrivate &p = CacheDbPrivate::ref ();
    QSqlQuery query(p.db);
    query.setForwardOnly (true);

    cookies.clear ();
    QString domain, path;
    bool isHttpOnly, isSecure, isSession;
    QByteArray name, value;
    quint32 expiration;

    bool rv =
    query.exec ("SELECT " GV_CJ_DOMAIN ","
                          GV_CJ_EXPIRATION ","
                          GV_CJ_HTTP_ONLY ","
                          GV_CJ_IS_SECURE ","
                          GV_CJ_IS_SESSION ","
                          GV_CJ_NAME ","
                          GV_CJ_PATH ","
                          GV_CJ_VALUE " "
                "FROM " GV_COOKIEJAR_TABLE);
    Q_ASSERT(rv); Q_UNUSED(rv);
    while (query.next ()) {
        domain      = query.value(0).toString ();
        expiration  = query.value(1).toUInt ();
        isHttpOnly  = query.value(2).toBool ();
        isSecure    = query.value(3).toBool ();
        isSession   = query.value(4).toBool ();
        name        = query.value(5).toByteArray ();
        path        = query.value(6).toString ();
        value       = query.value(7).toByteArray ();

        QNetworkCookie cookie(name, value);
        cookie.setDomain (domain);
        if (!isSession) {
            cookie.setExpirationDate (QDateTime::fromTime_t (expiration));
        }
        cookie.setHttpOnly (isHttpOnly);
        cookie.setSecure (isSecure);
        cookie.setPath (path);

        cookies.append (cookie);
    }

    return (true);
}//CacheDb::saveCookies

bool
CacheDb::clearCookies()
{
    CacheDbPrivate &p = CacheDbPrivate::ref ();
    QSqlQuery query(p.db);
    query.setForwardOnly (true);

    bool rv = query.exec("DELETE FROM " GV_COOKIEJAR_TABLE);
    Q_ASSERT(rv);

    return (rv);
}//CacheDb::clearCookies