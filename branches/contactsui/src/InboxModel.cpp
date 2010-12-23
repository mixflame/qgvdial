#include "InboxModel.h"
#include "Singletons.h"
#include "GVAccess.h"

InboxModel::InboxModel (QObject * parent)
: QSqlQueryModel (parent)
{
    QHash<int, QByteArray> roles;
    roles[IN_TypeRole]  = "type";
    roles[IN_TimeRole]  = "time";
    roles[IN_NameRole]  = "name";
    roles[IN_NumberRole]= "number";
    roles[IN_Link]      = "link";
    roles[IN_TimeDetail]= "time_detail";
    setRoleNames(roles);
}//InboxModel::InboxModel

int
InboxModel::rowCount (const QModelIndex &parent /* = QModelIndex()*/ ) const
{
    CacheDatabase &dbMain = Singletons::getRef().getDBMain ();
    return (dbMain.getInboxCount ());
}//InboxModel::rowCount

QVariant
InboxModel::data (const QModelIndex &index,
                        int          role ) const
{
    QVariant var;

    do // Begin cleanup block (not a loop)
    {
        int column = -1;
        switch (role)
        {
        case Qt::DisplayRole:
        case Qt::EditRole:
            column = index.column ();
            break;
        case IN_Link:
            column = 0;
            break;
        case IN_TypeRole:
            column = 1;
            break;
        case IN_TimeRole:
        case IN_TimeDetail:
            column = 2;
            break;
        case IN_NameRole:
            column = 3;
            break;
        case IN_NumberRole:
            column = 4;
            break;
        }

        // Pick up the data from the base class
        var = QSqlQueryModel::data (index.sibling(index.row (), column),
                                    Qt::EditRole);

        if (0 == column)        // GV_IN_ID
        {
            QString strLink = var.toString ();
            if (0 == strLink.size ()) {
                qWarning ("Inbox: Invalid link: Blank!");
                var.clear ();
                break;
            }
        }
        else if (1 == column)   // GV_IN_TYPE
        {
            char chType = var.toChar().toAscii ();
            QString strDisp = type_to_string ((GVH_Event_Type) chType);
            var.clear ();
            if (0 == strDisp.size ()) {
                qWarning () << "Inbox: Entry type could not be deciphered: "
                            << chType;
                break;
            }

            var = strDisp;
        }
        else if (2 == column)   // GV_IN_ATTIME
        {
            bool bOk = false;
            quint64 num = var.toULongLong (&bOk);
            var.clear ();
            if (!bOk) break;

            QDateTime dt = QDateTime::fromTime_t (num);
            QString strDisp;
            QDate currentDate = QDate::currentDate ();
            int daysTo = dt.daysTo (QDateTime::currentDateTime ());
            if (IN_TimeDetail == role) {
                if (0 == daysTo) {
                    strDisp = "today at " + dt.toString ("hh:mm:ss");
                } else if (1 == daysTo) {
                    strDisp = "yesterday at " + dt.toString ("hh:mm:ss");
                } else {
                    strDisp = "on "
                              + dt.toString ("dddd, dd-MMM")
                              + " at "
                              + dt.toString ("hh:mm:ss");
                }
            } else {
                if (0 == daysTo) {
                    strDisp = "at " + dt.toString ("hh:mm");
                } else if (1 == daysTo) {
                    strDisp = "yesterday";
                } else if (daysTo < currentDate.dayOfWeek ()) {
                    strDisp = "on " + dt.toString ("dddd");
                } else if (daysTo < (currentDate.dayOfWeek () + 7)) {
                    strDisp = "last week";
                } else {
                    strDisp = "on " + dt.toString ("dd-MMM");
                }
            }

            var = strDisp;
        }
        else if (3 == column)   // GV_IN_DISPNUM
        {
            QString strNum = var.toString ();
            var.clear ();
            if (0 == strNum.size ()) {
                qWarning ("Inbox: Friendly number is blank in entry");
                break;
            }
            if (!GVAccess::isNumberValid (strNum)) {
                qWarning () << "Inbox: Display phone number is invalid : "
                            << strNum;
                break;
            }

            GVAccess::simplify_number (strNum);

            CacheDatabase &dbMain = Singletons::getRef().getDBMain ();
            GVContactInfo info;
            if (dbMain.getContactFromNumber (strNum, info))
            {
                var = info.strName;
                break;
            }

            qDebug () << "Inbox: Number could not be identified: " << strNum
                      << "Labeling it as unknown.";
            var = "Unknown";
        }
        else if (4 == column)   // GV_IN_PHONE
        {
            QString strNum = var.toString ();
            var.clear ();
            if (0 == strNum.size ()) {
                qWarning ("Inbox: Number is blank in entry");
                break;
            }
            if (strNum.startsWith ("Unknown")) {
                var = "Unknown";
            }
            if (!GVAccess::isNumberValid (strNum)) {
                qWarning () << "Inbox: Actual phone number is invalid : "
                            << strNum;
                break;
            }

            GVAccess::beautify_number (strNum);
            var = strNum;
        }
        else
        {
            var.clear ();
            qWarning () << "Invalid data column requested in Inbox view: "
                        << column;
        }
    } while (0); // End cleanup block (not a loop)

    return (var);
}//InboxModel::data

QString
InboxModel::type_to_string (GVH_Event_Type Type)
{
    QString strReturn;
    switch (Type)
    {
    case GVHE_Placed:
        strReturn = "Placed";
        break;
    case GVHE_Received:
        strReturn = "Received";
        break;
    case GVHE_Missed:
        strReturn = "Missed";
        break;
    case GVHE_Voicemail:
        strReturn = "Voicemail";
        break;
    case GVHE_TextMessage:
        strReturn = "SMS";
        break;
    default:
        break;
    }
    return (strReturn);
}//InboxModel::type_to_string

GVH_Event_Type
InboxModel::string_to_type (const QString &strType)
{
    GVH_Event_Type Type = GVHE_Unknown;

    do // Begin cleanup block (not a loop)
    {
        if (0 == strType.compare ("Placed", Qt::CaseInsensitive))
        {
            Type = GVHE_Placed;
            break;
        }
        if (0 == strType.compare ("Received", Qt::CaseInsensitive))
        {
            Type = GVHE_Received;
            break;
        }
        if (0 == strType.compare ("Missed", Qt::CaseInsensitive))
        {
            Type = GVHE_Missed;
            break;
        }
        if (0 == strType.compare ("Voicemail", Qt::CaseInsensitive))
        {
            Type = GVHE_Voicemail;
            break;
        }
        if (0 == strType.compare ("SMS", Qt::CaseInsensitive))
        {
            Type = GVHE_TextMessage;
            break;
        }
    } while (0); // End cleanup block (not a loop)

    return (Type);
}//InboxModel::string_to_type
