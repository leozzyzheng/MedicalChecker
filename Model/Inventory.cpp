#include "Inventory.h"

Inventory::Inventory()
{
}

void Inventory::setData(int Id, QString InventoryName, int num)
{
    Inven i;
    i.name = InventoryName;
    i.num = num;
    m_data[Id] = i;
}

int Inventory::getNum(int Id)
{
    std::map<int,Inven>::iterator it = m_data.find(Id);

    if(it != m_data.end())
        return it->second.num;
    else
        return 0;
}

QString Inventory::getName(int Id)
{
    std::map<int,Inven>::iterator it = m_data.find(Id);

    if(it != m_data.end())
        return it->second.name;
    else
        return QString();
}

void Inventory::clear()
{
    m_data.clear();
}
