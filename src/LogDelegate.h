#ifndef LOGDELEGATE_H
#define LOGDELEGATE_H

#include <QStyledItemDelegate>

class LogDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LogDelegate(class Log*soruce, class FilteredLog *proxy);

    ~LogDelegate();
    void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    void setLog(class Log* soruce);
    void setLogFilter(class FilteredLog *proxy);


private:
    class LogDelegatePrivate *d;
    
};

#endif // LOGDELEGATE_H
