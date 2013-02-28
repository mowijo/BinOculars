#include "GlobalEventFilter.h"

#include <QKeyEvent>
#include <QListWidget>
#include <QDebug>

class GlobalEventFilterPrivate  : QObject
{

    Q_OBJECT

public:
    GlobalEventFilterPrivate(GlobalEventFilter *p)
        : QObject(p)
    {
        isselectorvisible = false;
        w = new QListWidget(root);
        w->addItems(QStringList() << "a" << "B" << "C" << "D");
        w->hide();
        w->installEventFilter(p);
        w->setWindowFlags( Qt::FramelessWindowHint  );

    }
    QWidget *root;
    QListWidget *w;
    bool isselectorvisible;
};

#include "GlobalEventFilter.moc"

GlobalEventFilter::GlobalEventFilter(QWidget *root)
    : QObject(root)
{
    d = new GlobalEventFilterPrivate(this);
    d->root = root;
    d->root->installEventFilter(this);
    QList<QWidget *> widgets = d->root->findChildren<QWidget *>();
    foreach(QWidget *w, widgets)
    {
        w->installEventFilter(this);
    }
}


bool GlobalEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if(ke->key() == Qt::Key_Tab && (ke->modifiers() & Qt::ControlModifier) )
        {
            if(d->isselectorvisible)
            {
                qDebug() << "Bladrer";
                event->ignore();
            }
            else
            {
                d->isselectorvisible = true;
                d->w->show();

                QPoint pos((d->root->width() - d->w->width())/2,
                        (d->root->height() - d->w->height())/2);

                d->w->move(d->root->mapToParent(pos));
                event->ignore();
            }
        }



    }

    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if(ke->key() == Qt::Key_Control)
        {
            d->isselectorvisible = false;
            d->w->hide();
            event->ignore();
        }
    }




    if(event->type() == QEvent::ChildAdded)
    {
        QChildEvent *ce = static_cast<QChildEvent*>(event);
        ce->child()->installEventFilter(this);
    }
    return QObject::eventFilter(obj, event);
}
