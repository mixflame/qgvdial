/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c AccountManagerProxy -p accountmanagerproxy.h:accountmanagerproxy.cpp org.freedesktop.Telepathy.AccountManager.xml org.freedesktop.Telepathy.AccountManager
 *
 * qdbusxml2cpp is Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "accountmanagerproxy.h"

/*
 * Implementation of interface class AccountManagerProxy
 */

AccountManagerProxy::AccountManagerProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

AccountManagerProxy::~AccountManagerProxy()
{
}

