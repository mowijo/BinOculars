#ifndef LOGMODELFILTER_H
#define LOGMODELFILTER_H

#include <QSortFilterProxyModel>

class LogModelFilter : public QSortFilterProxyModel
{

public:
    LogModelFilter();
    ~LogModelFilter();

    void setLogModel(class LogModel *model) ;

protected:
    bool filterAcceptsRow ( int source_row, const QModelIndex & source_parent ) const;

private:
    class LogModelFilterPrivate *d;
};

#endif // LOGMODELFILTER_H
