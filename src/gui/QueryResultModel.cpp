#include "QueryResultModel.h"

#include <QSqlResult>
#include <QSqlRecord>

#include <QDebug>


namespace Gui
{

class QueryResultModelPrivate
{
public:
    QList<QList<QVariant>*> records;
    QList<QString> headers;
};


QueryResultModel::QueryResultModel(QSqlQuery &q)
    : QAbstractTableModel()
{
    d = new QueryResultModelPrivate;
    for(int i = 0; i < q.record().count(); i++)
    {
        d->headers << q.record().fieldName(i);
    }

    while(q.next())
    {
        QList<QVariant> *fields = new QList<QVariant>();
        for(int i = 0; i < q.record().count(); i++)
        {
            fields->append(q.value(i));
        }
        d->records << fields;
    }

}

QueryResultModel::QueryResultModel()
{
    d = new QueryResultModelPrivate;
}

typedef QList<QVariant>* RECORD;

QueryResultModel * QueryResultModel::clone() const
{
    QueryResultModel *qrm = new QueryResultModel;
    qrm->d->headers = d->headers;
    foreach(RECORD r, d->records)
    {
        QList<QVariant> *fields = new QList<QVariant>();
        foreach(QVariant v, *r)
        {
            fields->append(v);
        }
        qrm->d->records.append(fields);
    }
    return qrm;
}

QueryResultModel::~QueryResultModel()
{
    while(d->records.size() > 0)
    {
        delete d->records.takeFirst();
    }
    delete d;
}

int QueryResultModel::rowCount(const QModelIndex &parent) const
{
    return d->records.size();
}

int QueryResultModel::columnCount(const QModelIndex &parent) const
{
    return d->headers.size();
}

QVariant QueryResultModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        QList<QVariant>* fields = d->records[index.row()];
        return fields->at(index.column());
    }
    return QVariant();
}

QVariant QueryResultModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        return d->headers[section];
    }
    return QVariant();
}

} // namespace Gui
