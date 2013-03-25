#include "Log.h"
#include <QSqlError>
#include <QColor>
#include <math.h>

namespace Model
{


class LogPrivate : QObject
{

    Q_OBJECT

private:
    Log *logmodel;

public:

    QList<QSqlQuery> queries;

    LogPrivate(Log *p) : QObject(p)
    {
        logmodel = p;
    }


};

#include "Log.moc"

Log::Log(QObject *parent) :
    QAbstractItemModel(parent)
{
    d = new LogPrivate(this);
}

QModelIndex Log::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QVariant Log::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0) return QVariant();
    if(index.row() >= rowCount()) return QVariant();
    int queryidx = floor(index.row() / 2);
    QSqlQuery q = d->queries[queryidx];
    if(Qt::DisplayRole == role)
    {
        if(index.column() == 0)
        {
            if( ! isRowForErrorStatus(index.row()) )
            {
                return q.lastQuery();
            }
            else
            {
                if(q.lastError().type() == QSqlError::NoError) return "OK";
                else return q.lastError().text();
            }
        }
        else if(index.column() == 1)
        {
            return q.lastError().type() == QSqlError::NoError;
        }
        else if(index.column() == 2)
        {
            return isRowForErrorStatus(index.row());
        }
    }
    if(Qt::DecorationRole == role)
    {
        if(index.column() == 0)
        {
            if( isRowForErrorStatus(index.row()) )
            {
                return QVariant();
            }
            else
            {
                return wasSuccessfull(index.row()) ? QColor(Qt::green) : QColor(Qt::red);
            }
        }
    }
    else
    {
        return QVariant();
    }
    return QVariant();
}

int Log::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QModelIndex Log::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int Log::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) return 0;
    return d->queries.count() * 2;
}

bool Log::wasSuccessfull(int row) const
{
    int queryidx = floor(row / 2);
    QSqlQuery q = d->queries[queryidx];
    return q.lastError().type() == QSqlError::NoError;

}

void Log::addEntry(const QSqlQuery &query)
{
    beginInsertRows(QModelIndex(), d->queries.size(), d->queries.size()+1);
    d->queries << query;
    endInsertRows();
    emit entryAdded(query);
}


bool Log::isRowForErrorStatus(int row) const
{
    int queryidx = floor(row / 2);
    return (queryidx * 2) != row;

}

} // namespace Model
