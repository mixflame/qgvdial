/*
qgvdial is a cross platform Google Voice Dialer
Copyright (C) 2010  Yuvraaj Kelkar

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

#ifndef TPCALLOUTINITIATOR_H
#define TPCALLOUTINITIATOR_H

#include "CalloutInitiator.h"

#include <TelepathyQt4/AccountManager>
#include <TelepathyQt4/SharedPtr>
#include <TelepathyQt4/PendingReady>

class TpCalloutInitiator : public CalloutInitiator
{
    Q_OBJECT

private:
    TpCalloutInitiator (Tp::AccountPtr act, QObject *parent = 0);

public:
    QString name ();
    QString selfNumber ();
    bool isValid ();

public slots:
    void initiateCall (const QString &strDestination, void *ctx = NULL);
    bool sendDTMF(const QString &strTones);

private slots:
    void onConnectionChanged (const Tp::ConnectionPtr &connection);
    void onConnectionChanged (Tp::ConnectionStatus, Tp::ConnectionStatusReason);

    void onChannelReady (Tp::PendingOperation *op);
    void onConnectionReady (Tp::PendingOperation *op);

private:
    Tp::AccountPtr      account;
    QString             strActCmName;
    QString             strSelfNumber;

    //! Is this the buggy spirit (skype) TP-CM?
    bool                bIsSpirit;

    friend class CallInitiatorFactory;
};

#endif // TPCALLOUTINITIATOR_H