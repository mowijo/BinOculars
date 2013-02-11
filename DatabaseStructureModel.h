#ifndef DATABASESTRUCTUREMODEL_H
#define DATABASESTRUCTUREMODEL_H

#include <QAbstractItemModel>

class DatabaseStructureModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DatabaseStructureModel(class DataBase *database);
    int	columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QModelIndex	parent ( const QModelIndex & index ) const;
    int	rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
signals:

public slots:

private:
    class DatabaseStructureModelPrivate *d;
};

#endif // DATABASESTRUCTUREMODEL_H
