/*
qgvdial is a cross platform Google Voice Dialer
Copyright (C) 2009-2014  Yuvraaj Kelkar

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

#ifndef OSDEPENDANT_H
#define OSDEPENDANT_H

#include "global.h"
#include "IOsDependent.h"
#include "OSDCipher.h"
#include "OSDDirs.h"
#include "OSVer.h"

#define SKYPE_ENABLED 0

#if DESKTOP_OS && SKYPE_ENABLED
class SkypeClientFactory;
#endif

class OsDependant : public IOsDependant,
                    public OsdCipher,
                    public OsdDirs,
                    public OsVer
{
public:
    OsDependant(QObject *parent = NULL);

    inline QString getTempDir() { return _getTempDir (); }
    inline QString getDbDir() { return _getDbDir (); }
    inline QString getLogsDir() { return _getLogsDir (); }
    inline QString getOsDetails() { return _getOsDetails(); }
    inline QString getVmailDir() { return _getVmailDir(); }

    inline bool
    cipher(const QByteArray &byIn, QByteArray &byOut, bool bEncrypt) {
        return _cipher (byIn, byOut, bEncrypt);
    }

    void setMainWidget (QWidget *win);

#if DESKTOP_OS && SKYPE_ENABLED
    SkypeClientFactory &skypeClientFactory();
#endif

private:
#if DESKTOP_OS && SKYPE_ENABLED
    SkypeClientFactory *m_skypeClientFactory;
#endif
};

#endif // OSDEPENDANT_H
