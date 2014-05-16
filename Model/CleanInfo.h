#ifndef CLEANINFO_H
#define CLEANINFO_H

#include <map>
#include <vector>
#include <QString>
#include <qDebug>

class CleanInfo
{
public:
    typedef std::map<int, std::map< QString,QString> > DataMap;
    CleanInfo();

    void setContentTableData(int index,const QString & content);
    void setStaffTableData(int index,const QString & staff);
    QString getContentData(int index);
    QString getStaffData(int index);
    void setData(int index, std::map<QString,QString> & datamap);
    void setData(int index,const QString & key,const QString & value);
    QString getData(int index, QString &key);
    void pushId(int index);
    int getId(int index);
    int getContentTableSize();
    int getDataSize();
    int getStaffTableSize();
    void clear();
    void print();
    int getIdFromContent(QString content);

private:
    DataMap m_data;
    std::map <int,QString> m_mContentTable;
    std::map <QString,int> m_mContentToId;
    std::map <int,QString> m_mStaffTable;
    std::vector<int> m_vId;
};

#endif // CLEANINFO_H
