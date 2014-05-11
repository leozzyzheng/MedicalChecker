#ifndef MARCO_H
#define MARCO_H

#include <QObject>
#include <QString>

#define DATABASE_TYPE "QMYSQL"
#define DATABASE_HOSTNAME "115.28.226.229"
#define DATABASE_PORT 3306
#define DATABASE_USERNAME "yclj"
#define DATABASE_PASSWD "yclj"
#define DATABASE_DATABASENAME ""  //"clinic"

#define DATABASE_NOCONNECTING 0
#define DATABASE_CONNECTING 1
#define DATABASE_CONNECTED_SUCC 2
#define DATABASE_CONNECTED_FAIL 3

#define TRAINING_TIME_TAG       "trainingTime"
#define TRAINING_ADDR_TAG       "trainingAddr"
#define TRAINING_TYPE_TAG       "trainingType"
#define TRAINING_CONTENT_TAG    "trainingContent"
#define TRAINING_STAFF_TAG      "trainingStaff"
#define TRAINING_SUBMIT_TAG     "trainingSubmitTime"
#define TRAINING_STAFFID_TAG    "staffId"
#define TRAINING_STAFFSIGN_TAG  "IsSign_In"
#define TRAINING_TRAINID_TAG    "trainingId"
#define TRAINING_REMARK_TAG     "remark"

#define QML_TOPIC_FONT_FAMILY   "verdana,Lucida Sans,trebuchet ms,arial,sans-serif"
#define QML_FONT_BLUE_COLOR     "#1D568A"
#define QML_FONT_BLACK_COLOR    "#FFFFFF"
#define QML_FONT_WHITE_COLOR    "#000000"
#define QML_BACK_GRAY_COLOR     "#EEEEEE"
#define QML_BACK_BLUE_COLOR     "#1D568A"

class QmlMarco : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString trTime READ getTRAINING_TIME_TAG CONSTANT)
    Q_PROPERTY(QString trAdd READ getTRAINING_ADDR_TAG CONSTANT)
    Q_PROPERTY(QString trType READ getTRAINING_TYPE_TAG CONSTANT)
    Q_PROPERTY(QString trContent READ getTRAINING_CONTENT_TAG CONSTANT)
    Q_PROPERTY(QString trStaff READ getTRAINING_STAFF_TAG CONSTANT)
    Q_PROPERTY(QString trSubmit READ getTRAINING_SUBMIT_TAG CONSTANT)
    Q_PROPERTY(QString trStaffid READ getTRAINING_STAFFID_TAG CONSTANT)
    Q_PROPERTY(QString trSign READ getTRAINING_STAFFSIGN_TAG CONSTANT)
    Q_PROPERTY(QString trTrid READ getTRAINING_TRAINID_TAG CONSTANT)
    Q_PROPERTY(QString trRemark READ getTRAINING_REMARK_TAG CONSTANT)
    Q_PROPERTY(QString topicFontFa READ getQML_TOPIC_FONT_FAMILY CONSTANT)
    Q_PROPERTY(QString fontBlue READ getQML_FONT_BLUE_COLOR CONSTANT)
    Q_PROPERTY(QString fontBlack READ getQML_FONT_BLACK_COLOR CONSTANT)
    Q_PROPERTY(QString fontWhite READ getQML_FONT_WHITE_COLOR CONSTANT)
    Q_PROPERTY(QString backGray READ getQML_BACK_GRAY_COLOR CONSTANT)
    Q_PROPERTY(QString backBlue READ getQML_BACK_BLUE_COLOR CONSTANT)

public:
    QString getTRAINING_TIME_TAG() const
    {
        return TRAINING_TIME_TAG;
    }

    QString getTRAINING_ADDR_TAG() const
    {
        return TRAINING_ADDR_TAG;
    }

    QString getTRAINING_TYPE_TAG() const
    {
        return TRAINING_TYPE_TAG;
    }

    QString getTRAINING_CONTENT_TAG() const
    {
        return TRAINING_CONTENT_TAG;
    }

    QString getTRAINING_STAFF_TAG() const
    {
        return TRAINING_STAFF_TAG;
    }

    QString getTRAINING_SUBMIT_TAG() const
    {
        return TRAINING_SUBMIT_TAG;
    }

    QString getTRAINING_STAFFID_TAG() const
    {
        return TRAINING_STAFFID_TAG;
    }

    QString getTRAINING_STAFFSIGN_TAG() const
    {
        return TRAINING_STAFFSIGN_TAG;
    }

    QString getTRAINING_TRAINID_TAG() const
    {
        return TRAINING_TRAINID_TAG;
    }

    QString getTRAINING_REMARK_TAG() const
    {
        return TRAINING_REMARK_TAG;
    }

    QString getQML_TOPIC_FONT_FAMILY() const
    {
        return QML_TOPIC_FONT_FAMILY;
    }

    QString getQML_FONT_BLUE_COLOR() const
    {
        return QML_FONT_BLUE_COLOR;
    }

    QString getQML_FONT_BLACK_COLOR() const
    {
        return QML_FONT_BLACK_COLOR;
    }

    QString getQML_FONT_WHITE_COLOR() const
    {
        return QML_FONT_WHITE_COLOR;
    }

    QString getQML_BACK_GRAY_COLOR() const
    {
        return QML_BACK_GRAY_COLOR;
    }

    QString getQML_BACK_BLUE_COLOR() const
    {
        return QML_BACK_BLUE_COLOR;
    }
};

#endif // MARCO_H
