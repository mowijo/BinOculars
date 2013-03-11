#include "LogModelFilter.h"
#include "LogModel.h"
#include <QDebug>
class LogModelFilterPrivate
{
public:
    Log *logmodel;
};

FilteredLog::FilteredLog()
{
    d = new class LogModelFilterPrivate;
}

FilteredLog::~FilteredLog()
{
    delete d;
}

void FilteredLog::setLogModel(Log *model)
{
    d->logmodel = model;
    setSourceModel(model);
    connect(model, SIGNAL(entryAdded(QSqlQuery)), this, SLOT(invalidate()));
}

bool FilteredLog::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
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

void FilteredLog::addEntry(const QSqlQuery &query)
{
    d->logmodel->addEntry(query);
    invalidate();
}
