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
}

bool LogModelFilter::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(d->logmodel->isRowForErrorStatus(source_row))
    {
        if(d->logmodel->wasSuccessfull(source_row))
        {
            qDebug() << "Was successfill"<<source_row<<"returned true";
            return false;
        }
        else
        {
            qDebug() << "Was successfill"<<source_row<<"returned false";
            return true;
        }
    }
    return true;
}
