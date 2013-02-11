#include "DatabaseStructureModel.h"
#include "DataBase.h"
#include "Table.h"
#include <QDebug>

class DatabaseStructureModelPrivate
{
private:
    DatabaseStructureModel *p;

public:

    DataBase *db;

    DatabaseStructureModelPrivate(DatabaseStructureModel *p)
    {
        this->p = p;
    }

    bool isTableRow(QModelIndex parent)
    {
        return !parent.isValid();
    }

    bool isColumnRow(QModelIndex parent)
    {

    }

};

DatabaseStructureModel::DatabaseStructureModel(DataBase *database)
    : QAbstractItemModel()
{
    d = new DatabaseStructureModelPrivate(this);
    d->db = database;

}

int DatabaseStructureModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant DatabaseStructureModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(d->isTableRow(index.parent()))
        {
            Table *table = d->db->tables()[index.row()];
            switch (index.column())
            {
            case 0: return table->name();
            case 1: return "Table";
            case 2: return "";
            case 3: return table->creationSql().replace("\n","");
            }
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex DatabaseStructureModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int DatabaseStructureModel::rowCount(const QModelIndex &parent) const
{
    if(d->isTableRow(parent))
    {
        //This is a table row.
        return d->db->tables().count();
    }
    else
    {
        return 0;
    }
}

QModelIndex DatabaseStructureModel::index(int row, int column, const QModelIndex &parent) const
{
    if(d->isTableRow(parent))
    {
        return createIndex(row, column);
    }
    else return QModelIndex();
}
