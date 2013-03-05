#ifndef QUERYRESULTMODEL_H
#define QUERYRESULTMODEL_H

#include <QAbstractTableModel>
#include <QSqlQuery>

class QueryResultModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QueryResultModel(QSqlQuery &q);
    ~QueryResultModel();

    int rowCount(const QModelIndex & parent = QModelIndex() ) const;
    int columnCount(const QModelIndex & parent = QModelIndex() ) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole ) const;
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

    QueryResultModel * clone() const;

private:
    QueryResultModel();
    class QueryResultModelPrivate *d;
};

#endif // QUERYRESULTMODEL_H
