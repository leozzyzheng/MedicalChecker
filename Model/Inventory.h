#ifndef INVENTORY_H
#define INVENTORY_H
#include <map>
#include <QString>

class Inventory
{
public:
    Inventory();

    struct Inven
    {
        QString name;
        int num;
    };

    void setData(int Id,QString InventoryName, int num);
    int  getNum(int Id);
    QString getName(int Id);
    void clear();

private:
    std::map<int,Inven> m_data;
};

#endif // INVENTORY_H
