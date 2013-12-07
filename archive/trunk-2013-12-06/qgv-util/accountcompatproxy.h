/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c AccountCompatProxy -p accountcompatproxy.h:accountcompatproxy.cpp org.freedesktop.Telepathy.Account.xml com.nokia.Account.Interface.Compat
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef ACCOUNTCOMPATPROXY_H_1281150160
#define ACCOUNTCOMPATPROXY_H_1281150160

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface com.nokia.Account.Interface.Compat
 */
class AccountCompatProxy: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "com.nokia.Account.Interface.Compat"; }

public:
    AccountCompatProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~AccountCompatProxy();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> SetHasBeenOnline()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("SetHasBeenOnline"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void CompatPropertyChanged(const QVariantMap &in0);
};

namespace com {
  namespace nokia {
    namespace Account {
      namespace Interface {
        typedef ::AccountCompatProxy Compat;
      }
    }
  }
}
#endif
