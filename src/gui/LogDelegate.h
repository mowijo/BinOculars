#ifndef LOGDELEGATE_H
#define LOGDELEGATE_H

#include <QStyledItemDelegate>

namespace Model
{
    class Log;
    class FilteredLog;
}

class LogDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LogDelegate(Model::Log* soruce, Model::FilteredLog *proxy, QAbstractItemView *view);

    ~LogDelegate();
    void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    void setLog(Model::Log* soruce);
    void setLogFilter(Model::FilteredLog *proxy);


private:
    class LogDelegatePrivate *d;
    
};

#endif // LOGDELEGATE_H
