#include "QSqlQueryEx.h"

QSqlQueryEx::QSqlQueryEx(const QString &query):
    m_bCanExecute(true),
    m_pReply(NULL)
{
    m_sql = query;
    m_currCount = -1;
}

QSqlQueryEx::QSqlQueryEx(const QSqlQueryEx &other):
    m_pReply(NULL)
{
    m_id = other.getID();
    m_sql = other.getSqlString();
    m_bCanExecute = other.getExecutable();
    m_currCount = other.getCurrCount();
    m_size = other.size();
    m_numRowsAffected = other.numRowsAffected();
    m_bActive = other.isActive();
    m_vRecord = other.getAllData();
}

void QSqlQueryEx::setID(const QString &id)
{
    m_id = id;
}

const QString &QSqlQueryEx::getID() const
{
    return m_id;
}

QString QSqlQueryEx::getSqlString() const
{
    return m_sql;
}

void QSqlQueryEx::setSqlString(const QString &sql)
{
    m_vPre.clear();
    m_sql = sql;
}

void QSqlQueryEx::replaceHolder(const QString &holder, const QVariant &value)
{
    QString v = value.toString();
    m_sql.replace(holder,v);
}

void QSqlQueryEx::threaBindValue(const QString &holder, const QVariant &value)
{
    PrepareData data;
    data.holder = holder;
    data.value = value;
    m_vPre.push_back(data);
}

void QSqlQueryEx::setExecutable(bool excutable)
{
    m_bCanExecute = excutable;
}

bool QSqlQueryEx::getExecutable() const
{
    return m_bCanExecute;
}

QueryHelper * QSqlQueryEx::getHelper()
{
    return &m_helper;
}

void QSqlQueryEx::emitResult()
{
    m_helper.emitResult(this);
}

void QSqlQueryEx::emitError(QSqlErrorEx & error)
{
    m_helper.emitError(error, this);
}

bool QSqlQueryEx::exec()
{
    QString type;
    m_bActive = false;
    QNetworkAccessManager * pMgr = new QNetworkAccessManager();

    if(m_sql.contains("insert",Qt::CaseInsensitive))
        type = "insert";
    else if(m_sql.contains("update",Qt::CaseInsensitive))
    {
        type = "update";
    }
    else if(m_sql.contains("select",Qt::CaseInsensitive))
    {
        type = "select";
    }
    else
        return false;

    QString encodedSql = m_sql.replace("%","%25");
    encodedSql = m_sql.replace("\"","'");

    QNetworkRequest request(QUrl(DATABASE_URL));
    QJsonObject obj;
    obj.insert("type",type);
    obj.insert("sql",encodedSql);
    QJsonDocument doc(obj);
    QByteArray postData = doc.toJson(QJsonDocument::Compact);
    postData = "jsonStr="+postData;

    if(m_pReply)
    {
        m_pReply->abort();
        delete m_pReply;
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    qDebug()<<postData;

    m_pReply = pMgr->post(request,postData);

    QEventLoop eventLoop;
    QTimer timer;
    QObject::connect(pMgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QObject::connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)), &eventLoop, SLOT(quit()));
    QObject::connect(&timer,SIGNAL(timeout()),&eventLoop,SLOT(quit()));
    timer.start(30000);
    eventLoop.exec();       //block until finish

    if (timer.isActive()){
        timer.stop();
    } else {
        m_pReply->abort();
        m_error.setText("NetWork timeout!");
        return false;
    }

    if(m_pReply->error() != QNetworkReply::NoError)
    {
        m_error.setText(m_pReply->errorString());
        return false;
    }

    QJsonParseError * error =  new QJsonParseError();
    QByteArray dataGot = m_pReply->readAll();
    doc = QJsonDocument::fromJson(dataGot,error);

    qDebug()<<dataGot;
    m_error.setText("");

    if(error->error == QJsonParseError::NoError)
    {
        QJsonObject obj = doc.object();

        if(obj.value("error").toString() == "0")
        {
            m_currCount = -1;
            m_bActive = true;

            if(type == "select")
            {
                m_size = obj.value("rows").toInt();
                m_numRowsAffected = -1;

                QJsonArray array = obj.value("result").toArray();
                m_vRecord.clear();

                for(int i = 0; i < array.size(); ++i)
                {
                    QSqlRecordEx rec;
                    QJsonObject obj = array.at(i).toObject();
                    rec.push(obj.toVariantMap());
                    m_vRecord.push_back(rec);
                }
            }
            else
            {
                m_size = -1;
                m_numRowsAffected = obj.value("rows").toInt();
            }
        }
        else
        {
            m_error.setText(obj.value("error").toString());
        }
    }
    else
    {
        m_error.setText(error->errorString());
    }

    pMgr->deleteLater();
    delete error;

    if(m_error.text().isEmpty())
        return true;
    else
        return false;
}

bool QSqlQueryEx::next()
{
    ++m_currCount;

    if(m_currCount >= m_vRecord.size())
    {
        return false;
    }
    else
    {
        return true;
    }
}

QSqlRecordEx QSqlQueryEx::record() const
{
    if(m_currCount == -1 && m_vRecord.size() != 0)
        return m_vRecord[0];

    else if(m_currCount>= m_vRecord.size())
    {
        return QSqlRecordEx();
    }
    else
    {
        return m_vRecord[m_currCount];
    }
}

QVariant QSqlQueryEx::value(int index)
{
    if(m_currCount >= m_vRecord.size())
    {
        return QVariant();
    }
    else
    {
        return m_vRecord[m_currCount].value(index);
    }
}

int QSqlQueryEx::size() const
{
    return m_size;
}

int QSqlQueryEx::numRowsAffected() const
{
    return m_numRowsAffected;
}

QSqlErrorEx QSqlQueryEx::error() const
{
    return m_error;
}

bool QSqlQueryEx::isActive() const
{
    return m_bActive;
}

int QSqlQueryEx::getCurrCount() const
{
    return m_currCount;
}

QVector<QSqlRecordEx> QSqlQueryEx::getAllData() const
{
    return m_vRecord;
}




