#include "LogModelFilter.h"
#include "LogModel.h"
#include <QDebug>
class LogModelFilterPrivate
{
public:
    LogModel *logmodel;
};

LogModelFilter::LogModelFilter()
{
    d = new class LogModelFilterPrivate;
}

LogModelFilter::~LogModelFilter()
{
    delete d;
}

void LogModelFilter::setLogModel(LogModel *model)
{
    d->logmodel = model;
    setSourceModel(model);
    connect(model, SIGNAL(entryAdded(QSqlQuery)), this, SLOT(invalidate()));
}

bool LogModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{

    Q_UNUSED(source_parent);

    if(d->logmodel->isRowForErrorStatus(source_row))
    {
        if(d->logmodel->wasSuccessfull(source_row))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return true;
}

void LogModelFilter::addEntry(const QSqlQuery &query)
{
    d->logmodel->addEntry(query);
    invalidate();
}
