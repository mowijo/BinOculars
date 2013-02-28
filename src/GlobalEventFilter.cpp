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





    }
    QWidget *root;

};

#include "GlobalEventFilter.moc"

GlobalEventFilter::GlobalEventFilter(QWidget *root)
    : QListWidget(root)
{
    d = new GlobalEventFilterPrivate(this);

    hide();
    addItems(QStringList() << "a" << "B" << "C" << "D");
    setWindowFlags( Qt::FramelessWindowHint  );
    resize(300,400);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setCurrentRow(0);

    d->root = root;
    d->root->installEventFilter(this);
    QList<QWidget *> widgets = d->root->findChildren<QWidget *>();
    foreach(QWidget *w, widgets)
    {
        if(w == this) continue;
        w->installEventFilter(this);
    }
}


bool GlobalEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    static int counter = 0;
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if(ke->key() == Qt::Key_Tab && (ke->modifiers() & Qt::ControlModifier) )
        {
            if(isVisible())
            {
                int idx = currentRow();
                if(idx >= count()-1)
                {
                    idx = 0;
                }
                else{
                    idx++;
                }
                setCurrentRow(idx);
                event->ignore();
                return false;
            }
            else
            {
                show();
                setFocus();
                QPoint pos((d->root->width() - width())/2,
                           (d->root->height() - height())/2);
                move(d->root->mapToParent(pos));
                event->ignore();
                return false;
            }
        }



    }

    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        if(ke->key() == Qt::Key_Control)
        {
            hide();
            event->ignore();
            qDebug() << "Selected index is" << currentRow();
            return false;
        }
    }




    if(event->type() == QEvent::ChildAdded)
    {
        QChildEvent *ce = static_cast<QChildEvent*>(event);
        ce->child()->installEventFilter(this);
    }
    return QObject::eventFilter(obj, event);
}
