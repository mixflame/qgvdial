/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -v -a api_adapter -v api_server.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "api_adapter.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class CallServerAdaptor
 */

CallServerAdaptor::CallServerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

CallServerAdaptor::~CallServerAdaptor()
{
    // destructor
}

void CallServerAdaptor::Call(const QString &strNumber)
{
    // handle method call org.QGVDial.CallServer.Call
    QMetaObject::invokeMethod(parent(), "Call", Q_ARG(QString, strNumber));
}

/*
 * Implementation of adaptor class SettingsServerAdaptor
 */

SettingsServerAdaptor::SettingsServerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

SettingsServerAdaptor::~SettingsServerAdaptor()
{
    // destructor
}

int SettingsServerAdaptor::GetCurrentPhone()
{
    // handle method call org.QGVDial.SettingsServer.GetCurrentPhone
    int index;
    QMetaObject::invokeMethod(parent(), "GetCurrentPhone", Q_RETURN_ARG(int, index));
    return index;
}

QStringList SettingsServerAdaptor::GetPhoneNames()
{
    // handle method call org.QGVDial.SettingsServer.GetPhoneNames
    QStringList arrPhoneNames;
    QMetaObject::invokeMethod(parent(), "GetPhoneNames", Q_RETURN_ARG(QStringList, arrPhoneNames));
    return arrPhoneNames;
}

bool SettingsServerAdaptor::SetCurrentPhone(int index)
{
    // handle method call org.QGVDial.SettingsServer.SetCurrentPhone
    bool success;
    QMetaObject::invokeMethod(parent(), "SetCurrentPhone", Q_RETURN_ARG(bool, success), Q_ARG(int, index));
    return success;
}

/*
 * Implementation of adaptor class TextServerAdaptor
 */

TextServerAdaptor::TextServerAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

TextServerAdaptor::~TextServerAdaptor()
{
    // destructor
}

void TextServerAdaptor::Text(const QStringList &arrNumbers, const QString &strData)
{
    // handle method call org.QGVDial.TextServer.Text
    QMetaObject::invokeMethod(parent(), "Text", Q_ARG(QStringList, arrNumbers), Q_ARG(QString, strData));
}

void TextServerAdaptor::TextWithoutData(const QStringList &arrNumbers)
{
    // handle method call org.QGVDial.TextServer.TextWithoutData
    QMetaObject::invokeMethod(parent(), "TextWithoutData", Q_ARG(QStringList, arrNumbers));
}

QStringList TextServerAdaptor::getTextsByContact(const QString &strContact)
{
    // handle method call org.QGVDial.TextServer.getTextsByContact
    QStringList arrTexts;
    QMetaObject::invokeMethod(parent(), "getTextsByContact", Q_RETURN_ARG(QStringList, arrTexts), Q_ARG(QString, strContact));
    return arrTexts;
}

QStringList TextServerAdaptor::getTextsByDate(const QString &strStart, const QString &strEnd)
{
    // handle method call org.QGVDial.TextServer.getTextsByDate
    QStringList arrTexts;
    QMetaObject::invokeMethod(parent(), "getTextsByDate", Q_RETURN_ARG(QStringList, arrTexts), Q_ARG(QString, strStart), Q_ARG(QString, strEnd));
    return arrTexts;
}
