#ifndef INVENTORYPROXY_H
#define INVENTORYPROXY_H

#include "SqlEvent.h"
#include "Model/Inventory.h"

class InventoryProxy : public SqlEvent
{
    Q_OBJECT
public:
    InventoryProxy(QObject * parent = 0);
    void clear();
public slots:
    void update();
    int getNum(int id);
    QString getName(int id);

protected slots:
    virtual void innerError(QSqlError &error);
    virtual void innerFinished(QSqlQueryEx query);

private:
    Inventory m_data;
    QString m_ClinicName;
};

#endif // INVENTORYPROXY_H
