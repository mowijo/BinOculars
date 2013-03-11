#include "LogDelegate.h"
#include "Log.h"
#include "LogFilter.h"
#include <QFont>
#include <QApplication>

#include <QPainter>

class LogDelegatePrivate
{
public:
    Log *soruce;
    FilteredLog *proxy;
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


LogDelegate::LogDelegate(Log *soruce, FilteredLog *proxy)
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
    p->setFont(d->font);

    if(option.state & QStyle::State_Selected)
    {
        p->fillRect(option.rect, option.palette.highlight());
    }

    if(d->soruce->isRowForErrorStatus(sourceindex.row()))
    {
        if(!d->soruce->wasSuccessfull(sourceindex.row()))
        {
            text = ">> " + text;
        }
    }

    if(d->soruce->wasSuccessfull(sourceindex.row()))
    {
        p->setPen(QColor(0,128,0));
    }
    else
    {
        if(option.state & QStyle::State_Selected)
        {
            p->setPen(QColor(255,0,0));
        }
        else
        {
            p->setPen(QColor(128,0,0));
        }

    }


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
