#ifndef DATABASESTRUCTUREMODEL_H
#define DATABASESTRUCTUREMODEL_H

#include <QAbstractItemModel>

class DataBase;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(DataBase *db, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

private:
    class DataBase *db;
    class TreeItem *rootItem;
};


#endif // DATABASESTRUCTUREMODEL_H
