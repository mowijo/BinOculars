#include "DatabaseSelector.h"

#include <QKeyEvent>
#include <QListWidget>
#include <QDebug>

namespace Gui
{

class DatabaseSelectorPrivate  : QObject
{

    Q_OBJECT

private:

    DatabaseSelector *owner;

public:
    QWidget *root;

public:
    DatabaseSelectorPrivate(DatabaseSelector *p)
        : QObject(p)
    {
        owner = p;
    }


    void handleKeyRelease(QKeyEvent *ke)
    {

        if(!owner->isVisible()) return;
        if(ke->key() == Qt::Key_Control)
        {
            owner->hide();
            ke->ignore();
            emit owner->databaseIndexSelected(owner->currentRow());
        }
    }


    void handleKeyPress(QKeyEvent *ke)
    {
        if(ke->key() == Qt::Key_Tab && (ke->modifiers() & Qt::ControlModifier) )
        {
            if(owner->isVisible())
            {
                int idx = owner->currentRow();
                if(idx >= owner->count()-1)
                {
                    idx = 0;
                }
                else{
                    idx++;
                }
                owner->setCurrentRow(idx);
                ke->ignore();
            }
            else
            {
                if(owner->count() > 0)
                {
                    owner->show();
                    owner->setFocus();
                    QPoint pos((root->width() - owner->width())/2,
                               (root->height() - owner->height())/2);
                    owner->move(owner->mapFromParent(pos));
                }
                ke->ignore();
            }
        }
    }

};

#include "DatabaseSelector.moc"

DatabaseSelector::DatabaseSelector(QWidget *root)
    : QListWidget(root)
{
    d = new DatabaseSelectorPrivate(this);
    setHidden(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWindowFlags( Qt::FramelessWindowHint  );
    resize(300,300);
    setTextElideMode(Qt::ElideMiddle);

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


void DatabaseSelector::setCurrentDatabaseIndex(int index)
{
    if(index < 0) return;
    if(index >= count()) return;
    setCurrentRow(index);
}

void DatabaseSelector::setDatabaseList(const QStringList& list)
{
    clear();
    addItems(list);
    setTextElideMode(Qt::ElideMiddle);
}

bool DatabaseSelector::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        d->handleKeyPress(ke);
    }

    if(event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *ke = static_cast<QKeyEvent*>(event);
        d->handleKeyRelease(ke);
    }

    if(event->type() == QEvent::ChildAdded)
    {
        QChildEvent *ce = static_cast<QChildEvent*>(event);
        ce->child()->installEventFilter(this);
    }
    return QObject::eventFilter(obj, event);
}

} //  namespace Gui
