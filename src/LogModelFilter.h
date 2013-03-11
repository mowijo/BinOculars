#ifndef LOGMODELFILTER_H
#define LOGMODELFILTER_H

#include <QSortFilterProxyModel>
#include <QSqlQuery>

class FilteredLog : public QSortFilterProxyModel
{

public:
    FilteredLog();
    ~FilteredLog();

    void setLogModel(class Log *model) ;

protected:
    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;
    void addEntry(const QSqlQuery &query);

private:
    class LogModelFilterPrivate *d;
};

#endif // LOGMODELFILTER_H
