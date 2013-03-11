#include "LogDelegate.h"
#include "LogModel.h"
#include "LogModelFilter.h"

#include <QPainter>

class LogDelegatePrivate
{
public:
    LogModel *soruce;
    LogModelFilter *proxy;

};


LogDelegate::LogDelegate(LogModel *soruce, LogModelFilter *proxy)
    : QStyledItemDelegate()
{
    d = new LogDelegatePrivate();
    d->soruce = soruce;
    d->proxy = proxy;
}

void LogDelegate::paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QModelIndex sourceindex = d->proxy->mapToSource(index);
    //p->fillRect(option.rect, Qt::yellow);
    p->drawText(option.rect.left(), option.rect.top(),d->soruce->data(sourceindex, Qt::DisplayRole).toString());
}

QSize LogDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, 10);
}
