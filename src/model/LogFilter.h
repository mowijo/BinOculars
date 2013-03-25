#ifndef LOGFILTER_H
#define LOGFILTER_H

#include <QSortFilterProxyModel>
#include <QSqlQuery>

namespace Model
{

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
    class FilteredLogPrivate *d;
};

} // namespace Model

#endif // LOGFILTER_H
