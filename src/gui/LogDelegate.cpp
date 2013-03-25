#include <QAbstractItemView>
#include <QApplication>
#include <QDebug>
#include <QFont>
#include <QPainter>

#include <model/Log.h>
#include <model/LogFilter.h>

#include "LogDelegate.h"

class LogDelegatePrivate
{
public:
    Model::Log *soruce;
    Model::FilteredLog *proxy;
    QFont font;
    QFontMetrics *fontmetrics;
    QAbstractItemView *view;

    void updateFont()
    {
        font = QApplication::font();
        font.setStyleHint(QFont::Monospace);
        font.setFamily("Courier");

        if(fontmetrics) delete fontmetrics;
        fontmetrics = new QFontMetrics(font);


    }
};


LogDelegate::LogDelegate(Model::Log *soruce, Model::FilteredLog *proxy, QAbstractItemView *view)
    : QStyledItemDelegate()
{
    d = new LogDelegatePrivate();
    d->soruce = soruce;    
    d->proxy = proxy;
    d->view = view;

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
    QString text = d->soruce->data(sourceindex, Qt::DisplayRole).toString().replace("\n", QString(" ")+QChar(0x14A7)+" ");
    p->setFont(d->font);


    if(option.state & QStyle::State_Selected)
    {
        QItemSelectionModel *selection = d->view->selectionModel();
        bool upstairsneighborselected = selection->isRowSelected(index.row()-1, index.parent());
        bool downstairsneighborselected = selection->isRowSelected(index.row()+1, index.parent());

        int dx = 1;
        int dy = 1;
        int dh = 2;
        int dw = 2;

        if(upstairsneighborselected)
        {
            dy--;
            dh--;
        }
        if(downstairsneighborselected)
        {
            dh--;
        }

        int dashoffset = 0;
        int number_of_upstairsneighborsselected = 0;
        int r = index.row()-1;
        if(option.rect.height()%2)
        {
            while(selection->isRowSelected(r, index.parent()))
            {
                number_of_upstairsneighborsselected++;
                r--;
                if(r < 0) break;
            }
            dashoffset = number_of_upstairsneighborsselected%2;

        }


        p->fillRect(option.rect.x()+dx, option.rect.y()+dy, option.rect.width()-dw, option.rect.height()-dh, option.palette.highlight());

        QPen borderpen(Qt::CustomDashLine);
        borderpen.setColor(Qt::black);
        borderpen.setDashPattern(QVector<qreal>() << 1 << 1);
        borderpen.setDashOffset(dashoffset);
        p->setPen(borderpen);
        p->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
        p->drawLine(option.rect.topRight(), option.rect.bottomRight());
        if(!upstairsneighborselected)
        {
            p->drawLine(option.rect.topLeft(), option.rect.topRight());
        }
        if(!downstairsneighborselected)
        {
            p->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
        }

    }

    if(d->soruce->isRowForErrorStatus(sourceindex.row()))
    {
        if(!d->soruce->wasSuccessfull(sourceindex.row()))
        {
            text = tr("Error: %1").arg(text);
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

void LogDelegate::setLog(Model::Log *soruce)
{
    d->soruce = soruce;
}

void LogDelegate::setLogFilter(Model::FilteredLog *proxy)
{
    d->proxy = proxy;
}
