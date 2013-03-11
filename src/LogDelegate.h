#ifndef LOGDELEGATE_H
#define LOGDELEGATE_H

#include <QStyledItemDelegate>

class LogDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit LogDelegate(class LogModel *soruce, class LogModelFilter *proxy);
    void paint( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

private:
    class LogDelegatePrivate *d;
    
};

#endif // LOGDELEGATE_H
