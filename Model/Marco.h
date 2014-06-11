#ifndef MARCO_H
#define MARCO_H

#include <QObject>
#include <QString>

#define DATABASE_HOSTNAME               "115.28.226.229"
#define DATABASE_URL                    "http://115.28.226.229:8080/Clinic/DataController"

#define DATABASE_NOCONNECTING           0
#define DATABASE_CONNECTING             1
#define DATABASE_CONNECTED_SUCC         2
#define DATABASE_CONNECTED_FAIL         3

#define SIGNATURE_SEND_IP               "115.28.226.229"
#define SIGNATURE_SEND_PORT             ":8080"
#define SIGNATURE_PERFIX                "Clinic/signFile/"

#define TABLE_DAILY_CLEAN_TASK          "DailyCleanTask"
#define TABLE_DAILY_CLEAN_RECORD        "DailyCleanRecord"
#define TABLE_WEEKLY_CLEAN_TASK         "WeeklyCleanTask"
#define TABLE_WEEKLY_CLEAN_RECORD       "WeeklyCleanRecord"
#define TABLE_SUPPLY_TASK               "SupplyTask"
#define TABLE_SUPPLY_RECORD             "CleanSupplyRecord"
#define TABLE_CHECK_TASK                "CheckTask"
#define TABLE_CHECK_RECORD              "CheckRecord"
#define TABLE_USER                      "User"
#define TABLE_INVEN                     "Inventory"

#define USER_ID_TAG                     "userId"
#define USER_NAME_TAG                   "name"
#define USER_NUMBERID_TAG               "idnumber"

#define TRAINING_TIME_TAG               "trainingTime"
#define TRAINING_ADDR_TAG               "trainingAddr"
#define TRAINING_TYPE_TAG               "trainingType"
#define TRAINING_CONTENT_TAG            "trainingContent"
#define TRAINING_STAFF_TAG              "trainingStaff"
#define TRAINING_SUBMIT_TAG             "trainingSubmitTime"
#define TRAINING_STAFFID_TAG            "staffId"
#define TRAINING_STAFFSIGN_TAG          "IsSign_In"
#define TRAINING_TRAINID_TAG            "trainingId"
#define TRAINING_REMARK_TAG             "remark"

#define CLEAN_TASKCONTENT_TAG           "TaskContent"
#define CLEAN_STAFFID_TAG               "StaffId"
#define CLEAN_SIG_TAG                   "Signature"
#define CLEAN_SIGNSTAFFID_TAG           "SignStaffId"

#define DAILYCLEAN_TASKID_TAG           "DailyCleanTaskId"
#define DAILYCLEAN_TIME_TAG             "CleanTime"

#define WEEKLYCLEAN_TASKID_TAG          "WeeklyCleanTaskId"
#define WEEKLYCLEAN_TIME_TAG            "Week"

#define SUPPLY_TASKID_TAG               "SupplyTaskId"
#define SUPPLY_TIME_TAG                 "ReFillTime"

#define CHECK_TASKID_TAG                "CheckTaskId"
#define CHECK_CONTENT_TAG               "CheckContent"
#define CHECK_DAY_TAG                   "CheckWeekDay"
#define CHECK_STAFFID_TAG               "StaffId"
#define CHECK_TIME_TAG                  "CheckTime"
#define CHECK_SIG_TAG                   "Signature"

#define STER_TASKID_TAG                 "SterilizeTaskId"
#define STER_STIME_TAG                  "TaskStartTime"
#define STER_ETIME_TAG                  "TaskEndTime"
#define STER_INVEN_TAG                  "InventoryIds"
#define STER_CHECKTIME_TAG              "CheckTime"
#define STER_STAFFID_TAG                "StaffId"
#define STER_SIG_TAG                    "Signature"

#define INVEN_ID_TAG                    "InventoryId"
#define INVEN_NAME_TAG                  "Name"
#define INVEN_NUM_TAG                   "Amount"

#define QML_TOPIC_FONT_FAMILY           "verdana,Lucida Sans,trebuchet ms,arial,sans-serif"
#define QML_CHECK_FONT_FAMILY           "consolas,verdana,arial,sans-serif"
#define QML_FONT_YELLOW_COLOR           "#ff9933"
#define QML_FONT_DARKBLUE_COLOR         "#003366"
#define QML_FONT_BLUE_COLOR             "#1d568a"
#define QML_FONT_BLACK_COLOR            "#000000"
#define QML_FONT_WHITE_COLOR            "#ffffff"
#define QML_BACK_GRAY_COLOR             "#eeeeee"
#define QML_BACK_BLUE_COLOR             "#1d568a"
#define QML_DCLEAN_FONT_PXSIZE          16
#define QML_BORDER_COLOR                "#cccccc"
#define QML_SUPPLY_FONT_PXSIZE          14
#define QML_TOPIC_FONT_PXSIZE           28
#define QML_CHECK_FONT_PXSIZE           60

//this marco can auto register an marco "marco" to qml named "name"
#define REGISTER_MARCO(name,functionName,marco) \
    private: \
        Q_PROPERTY(QString name READ functionName CONSTANT) \
    public: \
        QString functionName() const \
        {   \
            return marco; \
        } \

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
    Q_PROPERTY(int dCleanFontpSize READ getQML_DCLEAN_FONT_PXSIZE CONSTANT)
    Q_PROPERTY(QString borderColor READ getQML_BORDER_COLOR CONSTANT)
    Q_PROPERTY(QString taskContent READ getCLEAN_TASKCONTENT_TAG CONSTANT)
    Q_PROPERTY(QString cleanSig READ getCLEAN_SIG_TAG CONSTANT)
    Q_PROPERTY(QString userName READ getUSER_NAME_TAG CONSTANT)
    Q_PROPERTY(int suppFontpSize READ getQML_SUPPLY_FONT_PXSIZE CONSTANT)
    Q_PROPERTY(int topicFontpSize READ getQML_TOPIC_FONT_PXSIZE CONSTANT)
    Q_PROPERTY(QString dCleanTaskId READ getDAILYCLEAN_TASKID_TAG CONSTANT)
    Q_PROPERTY(QString cleanStaffId READ getCLEAN_STAFFID_TAG CONSTANT)
    Q_PROPERTY(QString wCleanTaskId READ getWEEKLYCLEAN_TASKID_TAG CONSTANT)
    Q_PROPERTY(QString sCleanTaskId READ getSUPPLY_TASKID_TAG CONSTANT)
    Q_PROPERTY(QString checkFontFa READ getQML_CHECK_FONT_FAMILY CONSTANT)
    Q_PROPERTY(QString fontYellow READ getQML_FONT_YELLOW_COLOR CONSTANT)
    Q_PROPERTY(int checkFontpSize READ getQML_CHECK_FONT_PXSIZE CONSTANT)
    Q_PROPERTY(QString fontDarkBlue READ getQML_FONT_DARKBLUE_COLOR CONSTANT)
    Q_PROPERTY(QString sterSTime READ getSTER_STIME_TAG CONSTANT)
    Q_PROPERTY(QString sterETime READ getSTER_ETIME_TAG CONSTANT)
    Q_PROPERTY(QString sterId READ getSTER_TASKID_TAG CONSTANT)



    //auto marco usage
    //REGISTER_MARCO(trTime,tr,TRAINING_TIME_TAG)
    //REGISTER_MARCO(sterETime,te,STER_ETIME_TAG)

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

    int getQML_DCLEAN_FONT_PXSIZE() const
    {
        return QML_DCLEAN_FONT_PXSIZE;
    }

    QString getQML_BORDER_COLOR() const
    {
        return QML_BORDER_COLOR;
    }

    QString getCLEAN_TASKCONTENT_TAG() const
    {
        return CLEAN_TASKCONTENT_TAG;
    }

    QString getCLEAN_SIG_TAG() const
    {
        return CLEAN_SIG_TAG;
    }

    QString getUSER_NAME_TAG() const
    {
        return USER_NAME_TAG;
    }

    int getQML_SUPPLY_FONT_PXSIZE() const
    {
        return QML_SUPPLY_FONT_PXSIZE;
    }

    int getQML_TOPIC_FONT_PXSIZE() const
    {
        return QML_TOPIC_FONT_PXSIZE;
    }

    QString getDAILYCLEAN_TASKID_TAG() const
    {
        return DAILYCLEAN_TASKID_TAG;
    }

    QString getCLEAN_STAFFID_TAG() const
    {
        return CLEAN_STAFFID_TAG;
    }

    QString getWEEKLYCLEAN_TASKID_TAG() const
    {
        return WEEKLYCLEAN_TASKID_TAG;
    }

    QString getSUPPLY_TASKID_TAG() const
    {
        return SUPPLY_TASKID_TAG;
    }

    QString getQML_CHECK_FONT_FAMILY() const
    {
        return QML_CHECK_FONT_FAMILY;
    }

    QString getQML_FONT_YELLOW_COLOR() const
    {
        return QML_FONT_YELLOW_COLOR;
    }

    int getQML_CHECK_FONT_PXSIZE() const
    {
        return QML_CHECK_FONT_PXSIZE;
    }

    QString getQML_FONT_DARKBLUE_COLOR() const
    {
        return QML_FONT_DARKBLUE_COLOR;
    }

    QString getSTER_STIME_TAG() const
    {
        return STER_STIME_TAG;
    }

    QString getSTER_ETIME_TAG() const
    {
        return STER_ETIME_TAG;
    }

    QString getSTER_TASKID_TAG() const
    {
        return STER_TASKID_TAG;
    }
};

#endif // MARCO_H
