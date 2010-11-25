/*
 * This file was generated by dbusxml2cpp version 0.6
 * Command line was: dbusxml2cpp -i QtTelepathy/Common/BaseTypes -i QtTelepathy/Common/ConnectionTypes -a include/QtTelepathy/Core/connectionadaptor.h: xml/tp-conn.xml
 *
 * dbusxml2cpp is Copyright (C) 2006 Trolltech ASA. All rights reserved.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef CONNECTIONADAPTOR_H_1172489892
#define CONNECTIONADAPTOR_H_1172489892

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "connectiontypes.h"
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface org.freedesktop.Telepathy.Connection
 */
class ConnectionAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Telepathy.Connection")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.freedesktop.Telepathy.Connection\" >\n"
"    <method name=\"Connect\" />\n"
"    <method name=\"Disconnect\" />\n"
"    <method name=\"GetInterfaces\" >\n"
"      <arg direction=\"out\" type=\"as\" />\n"
"    </method>\n"
"    <method name=\"GetProtocol\" >\n"
"      <arg direction=\"out\" type=\"s\" />\n"
"    </method>\n"
"    <method name=\"GetSelfHandle\" >\n"
"      <arg direction=\"out\" type=\"u\" />\n"
"    </method>\n"
"    <method name=\"GetStatus\" >\n"
"      <arg direction=\"out\" type=\"u\" />\n"
"    </method>\n"
"    <method name=\"HoldHandles\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In1\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle_type\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"handles\" />\n"
"    </method>\n"
"    <method name=\"InspectHandles\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In1\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle_type\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"handles\" />\n"
"      <arg direction=\"out\" type=\"as\" />\n"
"    </method>\n"
"    <method name=\"ListChannels\" >\n"
"      <annotation value=\"org::freedesktop::Telepathy::ChannelInfoList\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"out\" type=\"a(osuu)\" />\n"
"    </method>\n"
"    <method name=\"ReleaseHandles\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In1\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle_type\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"handles\" />\n"
"    </method>\n"
"    <method name=\"RequestChannel\" >\n"
"      <arg direction=\"in\" type=\"s\" name=\"type\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle_type\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle\" />\n"
"      <arg direction=\"in\" type=\"b\" name=\"suppress_handler\" />\n"
"      <arg direction=\"out\" type=\"o\" />\n"
"    </method>\n"
"    <method name=\"RequestHandles\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"in\" type=\"u\" name=\"handle_type\" />\n"
"      <arg direction=\"in\" type=\"as\" name=\"names\" />\n"
"      <arg direction=\"out\" type=\"au\" />\n"
"    </method>\n"
"    <signal name=\"NewChannel\" >\n"
"      <arg type=\"o\" name=\"object_path\" />\n"
"      <arg type=\"s\" name=\"channel_type\" />\n"
"      <arg type=\"u\" name=\"handle_type\" />\n"
"      <arg type=\"u\" name=\"handle\" />\n"
"      <arg type=\"b\" name=\"suppress_handler\" />\n"
"    </signal>\n"
"    <signal name=\"StatusChanged\" >\n"
"      <arg type=\"u\" name=\"status\" />\n"
"      <arg type=\"u\" name=\"reason\" />\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    ConnectionAdaptor(QObject *parent);
    virtual ~ConnectionAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void Connect();
    void Disconnect();
    QStringList GetInterfaces();
    QString GetProtocol();
    uint GetSelfHandle();
    uint GetStatus();
    void HoldHandles(uint handle_type, const QList<uint> &handles);
    QStringList InspectHandles(uint handle_type, const QList<uint> &handles);
    org::freedesktop::Telepathy::ChannelInfoList ListChannels();
    void ReleaseHandles(uint handle_type, const QList<uint> &handles);
    QDBusObjectPath RequestChannel(const QString &type, uint handle_type, uint handle, bool suppress_handler);
    QList<uint> RequestHandles(uint handle_type, const QStringList &names);
Q_SIGNALS: // SIGNALS
    void NewChannel(const QDBusObjectPath &object_path, const QString &channel_type, uint handle_type, uint handle, bool suppress_handler);
    void StatusChanged(uint status, uint reason);
};

#endif
