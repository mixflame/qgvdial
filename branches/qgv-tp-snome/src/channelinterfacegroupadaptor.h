/*
 * This file was generated by dbusxml2cpp version 0.6
 * Command line was: dbusxml2cpp -i QtTelepathy/Common/BaseTypes -a include/QtTelepathy/Core/channelinterfacegroupadaptor.h: xml/tp-chan-iface-group.xml
 *
 * dbusxml2cpp is Copyright (C) 2006 Trolltech ASA. All rights reserved.
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef CHANNELINTERFACEGROUPADAPTOR_H_1172489890
#define CHANNELINTERFACEGROUPADAPTOR_H_1172489890

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include "basetypes.h"
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface org.freedesktop.Telepathy.Channel.Interface.Group
 */
class GroupAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.freedesktop.Telepathy.Channel.Interface.Group")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.freedesktop.Telepathy.Channel.Interface.Group\" >\n"
"    <method name=\"AddMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In0\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"contacts\" />\n"
"      <arg direction=\"in\" type=\"s\" name=\"message\" />\n"
"    </method>\n"
"    <method name=\"GetAllMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out1\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out2\" />\n"
"      <arg direction=\"out\" type=\"au\" name=\"current\" />\n"
"      <arg direction=\"out\" type=\"au\" name=\"local_pending\" />\n"
"      <arg direction=\"out\" type=\"au\" name=\"remote_pending\" />\n"
"    </method>\n"
"    <method name=\"GetGroupFlags\" >\n"
"      <arg direction=\"out\" type=\"u\" />\n"
"    </method>\n"
"    <method name=\"GetHandleOwners\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In0\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"handles\" />\n"
"      <arg direction=\"out\" type=\"au\" />\n"
"    </method>\n"
"    <method name=\"GetLocalPendingMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"out\" type=\"au\" />\n"
"    </method>\n"
"    <method name=\"GetMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"out\" type=\"au\" />\n"
"    </method>\n"
"    <method name=\"GetRemotePendingMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.Out0\" />\n"
"      <arg direction=\"out\" type=\"au\" />\n"
"    </method>\n"
"    <method name=\"GetSelfHandle\" >\n"
"      <arg direction=\"out\" type=\"u\" />\n"
"    </method>\n"
"    <method name=\"RemoveMembers\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In0\" />\n"
"      <arg direction=\"in\" type=\"au\" name=\"contacts\" />\n"
"      <arg direction=\"in\" type=\"s\" name=\"message\" />\n"
"    </method>\n"
"    <signal name=\"GroupFlagsChanged\" >\n"
"      <arg type=\"u\" name=\"added\" />\n"
"      <arg type=\"u\" name=\"removed\" />\n"
"    </signal>\n"
"    <signal name=\"MembersChanged\" >\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In1\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In2\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In3\" />\n"
"      <annotation value=\"QList&lt;uint>\" name=\"com.trolltech.QtDBus.QtTypeName.In4\" />\n"
"      <arg type=\"s\" name=\"message\" />\n"
"      <arg type=\"au\" name=\"added\" />\n"
"      <arg type=\"au\" name=\"removed\" />\n"
"      <arg type=\"au\" name=\"local_pending\" />\n"
"      <arg type=\"au\" name=\"remote_pending\" />\n"
"      <arg type=\"u\" name=\"actor\" />\n"
"      <arg type=\"u\" name=\"reason\" />\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    GroupAdaptor(QObject *parent);
    virtual ~GroupAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void AddMembers(const QList<uint> &contacts, const QString &message);
    QList<uint> GetAllMembers(QList<uint> &local_pending, QList<uint> &remote_pending);
    uint GetGroupFlags();
    QList<uint> GetHandleOwners(const QList<uint> &handles);
    QList<uint> GetLocalPendingMembers();
    QList<uint> GetMembers();
    QList<uint> GetRemotePendingMembers();
    uint GetSelfHandle();
    void RemoveMembers(const QList<uint> &contacts, const QString &message);
Q_SIGNALS: // SIGNALS
    void GroupFlagsChanged(uint added, uint removed);
    void MembersChanged(const QString &message, const QList<uint> &added, const QList<uint> &removed, const QList<uint> &local_pending, const QList<uint> &remote_pending, uint actor, uint reason);
};

#endif
