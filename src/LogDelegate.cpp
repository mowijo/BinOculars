#include "LogDelegate.h"
#include "LogModel.h"
#include "LogModelFilter.h"
#include <QFont>
#include <QApplication>

#include <QPainter>

class LogDelegatePrivate
{
public:
    LogModel *soruce;
    LogModelFilter *proxy;
    QFont font;
    QFontMetrics *fontmetrics;

    void updateFont()
    {
        font = QApplication::font();
        font.setStyleHint(QFont::Monospace);
        font.setFamily("Courier");

        if(fontmetrics) delete fontmetrics;
        fontmetrics = new QFontMetrics(font);


    }
};


LogDelegate::LogDelegate(LogModel *soruce, LogModelFilter *proxy)
    : QStyledItemDelegate()
{
    d = new LogDelegatePrivate();
    d->soruce = soruce;
    d->proxy = proxy;
    d->fontmetrics = 0;
    d->updateFont();

}

LogDelegate::~LogDelegate()
{
    if(d->fontmetrics) delete d->fontmetrics;
    delete d;
}

void LogDelegate::paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QModelIndex sourceindex = d->proxy->mapToSource(index);
    QString text = d->soruce->data(sourceindex, Qt::DisplayRole).toString();
    p->setPen(Qt::black);
    if(d->soruce->isRowForErrorStatus(sourceindex.row()))
    {
        if(!d->soruce->wasSuccessfull(sourceindex.row()))
        {
            text = "!! " + text;
        }
    }

    if(d->soruce->wasSuccessfull(sourceindex.row()))
    {
        p->setPen(QColor(0,128,0));
    }
    else
    {
        p->setPen(QColor(128,0,0));
    }

    p->setFont(d->font);

    p->drawText(
                option.rect.left(),
                option.rect.bottom() - d->fontmetrics->boundingRect(text).height()/3.25,
                text
                );
}

QSize LogDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, d->fontmetrics->height()*1.25);
}
