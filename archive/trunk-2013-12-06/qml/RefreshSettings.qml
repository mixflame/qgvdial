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

import Qt 4.7
import "meego"
import "generic"
import "s3"

Item {
    id: container

    signal sigDone(bool bSave)
    signal sigRefreshChanges(bool bRefreshEnable,
                             string contactsPeriod, string inboxPeriod,
                             bool bMqEnable, string host, int port, string topic)
    signal sigRefreshPeriodSettings

    function setMqValues(bEnable, host, port, topic) {
        console.debug ("QML: Setting Mq settings")
        mqSupport.checked = bEnable;
        textMqServer.text = host;
        textMqPort.text = port;
        textMqTopic.text = topic;
    }

    function setRefreshValues(bEnable, contactsPeriod, inboxPeriod) {
        console.debug ("QML: Setting Refresh settings")
        periodicRefresh.checked = bEnable;
        textContactsRefreshPeriod.text = contactsPeriod;
        textInboxRefreshPeriod.text = inboxPeriod;
    }

    height: mainColumn.height

    Column {
        id: mainColumn
        anchors {
            top: parent.top
            left: parent.left
        }
        spacing: 2
        width: parent.width

        // Internal property
        property real subTextPointSize: (8 * g_fontMul)
        property real fontPointMultiplier: 8.0 / 10.0

        QGVRadioButton {
            id: periodicRefresh
            width: parent.width

            text: "Enable periodic refresh"

            pointSize: (8 * g_fontMul)
        }//QGVRadioButton (enable periodicRefresh)

        Row {
            width: parent.width
            height: lblContactsRefreshPeriod.height
            spacing: 2

            opacity: (periodicRefresh.checked ? 1 : 0)

            QGVLabel {
                id: lblContactsRefreshPeriod
                text: "Refresh contacts (min)"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("Refresh contacts (min)")

            QGVTextInput {
                id: textContactsRefreshPeriod
                width: parent.width - lblContactsRefreshPeriod.width
                height: lblContactsRefreshPeriod.height
                anchors.verticalCenter: parent.verticalCenter
                text: "30"
                validator: IntValidator { bottom: 0; top: 65535 }
                KeyNavigation.tab: textInboxRefreshPeriod
                KeyNavigation.backtab: textInboxRefreshPeriod
                fontPointMultiplier: mainColumn.fontPointMultiplier
            }//QGVTextInput (contact refresh period)

            QGVLabel {
                text: "sec"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("sec")
        }// Row (Contacts refresh period)

        Row {
            width: parent.width
            height: lblInboxRefreshPeriod.height
            spacing: 2

            opacity: (periodicRefresh.checked ? 1 : 0)

            QGVLabel {
                id: lblInboxRefreshPeriod
                text: "Refresh inbox (min)"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("Refresh inbox (min)")

            QGVTextInput {
                id: textInboxRefreshPeriod
                width: parent.width - lblInboxRefreshPeriod.width
                height: lblInboxRefreshPeriod.height
                anchors.verticalCenter: parent.verticalCenter
                text: "30"
                validator: IntValidator { bottom: 0; top: 65535 }
                KeyNavigation.tab: textContactsRefreshPeriod
                KeyNavigation.backtab: textContactsRefreshPeriod
                fontPointMultiplier: mainColumn.fontPointMultiplier
            }//QGVTextInput (inbox refresh period)
        }// Row (Inbox refresh period)

        QGVRadioButton {
            id: mqSupport
            width: parent.width

            text: "Enable mosquitto"
            pointSize: mainColumn.subTextPointSize
        }// QGVRadioButton (enable mqSupport)

        Row {
            width: parent.width
            height: lblHost.height
            spacing: 2
            opacity: (mqSupport.checked ? 1 : 0)

            QGVLabel {
                id: lblHost
                text: "Host:"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("Host:")

            QGVTextInput {
                id: textMqServer
                width: parent.width - lblHost.width
                height: lblHost.height
                anchors.verticalCenter: parent.verticalCenter
                text: "mosquitto.example.com"
                KeyNavigation.tab: textMqPort
                KeyNavigation.backtab: textMqTopic
                fontPointMultiplier: mainColumn.fontPointMultiplier
            }//QGVTextInput (mq server)
        }// Row (Mq server)

        Row {
            width: parent.width
            height: lblPort.height
            spacing: 2

            opacity: (mqSupport.checked ? 1 : 0)

            QGVLabel {
                id: lblPort
                text: "Port:"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("Port:")

            QGVTextInput {
                id: textMqPort
                width: parent.width - lblPort.width
                height: lblPort.height
                anchors.verticalCenter: parent.verticalCenter
                text: "1883"
                validator: IntValidator { bottom: 0; top: 65535 }
                KeyNavigation.tab: textMqTopic
                KeyNavigation.backtab: textMqServer
                fontPointMultiplier: mainColumn.fontPointMultiplier
            }//QGVTextInput (mq port)
        }// Row (Mq port)

        Row {
            width: parent.width
            height: lblTopic.height
            spacing: 2
            opacity: (mqSupport.checked ? 1 : 0)

            QGVLabel {
                id: lblTopic
                text: "Topic to sub:"
                anchors.verticalCenter: parent.verticalCenter
                height: paintedHeight + 2
            }//QGVLabel ("Topic to sub:")

            QGVTextInput {
                id: textMqTopic
                width: parent.width - lblTopic.width
                height: lblTopic.height
                anchors.verticalCenter: parent.verticalCenter
                text: "gv_notify"
                KeyNavigation.tab: textMqServer
                KeyNavigation.backtab: textMqPort
                fontPointMultiplier: mainColumn.fontPointMultiplier
            }//QGVTextInput (mq topic)
        }// Row (Mq topic to subscribe to)

        SaveCancel {
            anchors {
                left: parent.left
                leftMargin: 1
            }
            width: parent.width - 1

            onSigSave: {
                container.sigRefreshChanges (periodicRefresh.checked,
                                             textContactsRefreshPeriod.text,
                                             textInboxRefreshPeriod.text,
                                             mqSupport.checked,
                                             textMqServer.text,
                                             textMqPort.text,
                                             textMqTopic.text);
                container.sigDone(true);
            }

            onSigCancel: {
                container.sigRefreshPeriodSettings();
                container.sigDone(false);
            }
        }// Save and cancel buttons
    }// Column
}// Item (top level)