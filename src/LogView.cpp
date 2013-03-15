#include "LogView.h"
#include <QKeyEvent>
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QAction>
#include <QItemSelectionModel>
#include <QMenu>

class LogViewPrivate : public QObject
{
    Q_OBJECT

private:
    LogView *logview;

public:

    QAction *select_all_lines_action;
    QAction *select_successfull_lines_action;
    QAction *select_failed_lines_action;
    QAction *select_failed_lines_and_errormessages_action;

    QMenu contextmenu;


    LogViewPrivate(LogView* p) : QObject(p)
    {
        logview = p;

        select_successfull_lines_action = new QAction(tr("Select succesfull lines"), p);
        select_successfull_lines_action->setShortcut(QKeySequence("CTRL+A,CTRL+S"));
        select_successfull_lines_action->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(select_successfull_lines_action);
        connect(select_successfull_lines_action, SIGNAL(triggered()), this, SLOT(selectTheSuccessfullEntries()));


        select_all_lines_action = new QAction(tr("Select all entries"), p);
        select_all_lines_action->setShortcut(QKeySequence("CTRL+A,CTRL+E"));
        select_all_lines_action->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(select_all_lines_action);
        connect(select_all_lines_action, SIGNAL(triggered()), this, SLOT(selectAllEntries()));


        select_failed_lines_action = new QAction(tr("Select failed lines"), p);
        select_failed_lines_action->setShortcut(QKeySequence("CTRL+A,CTRL+F"));
        select_failed_lines_action->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(select_failed_lines_action);
        connect(select_failed_lines_action, SIGNAL(triggered()), this, SLOT(selectTheFailedEntries()));

        select_failed_lines_and_errormessages_action = new QAction(tr("Select failed lines and errormessages"), p);
        select_failed_lines_and_errormessages_action->setShortcut(QKeySequence("CTRL+SHIFT+A,CTRL+SHIFT+F"));
        select_failed_lines_and_errormessages_action->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(select_failed_lines_and_errormessages_action);
        connect(select_failed_lines_and_errormessages_action, SIGNAL(triggered()), this, SLOT(selectTheFailedEntriesAndErrorMessages()));



        contextmenu.addAction(select_all_lines_action);
        contextmenu.addAction(select_successfull_lines_action);
        contextmenu.addAction(select_failed_lines_action);
        contextmenu.addAction(select_failed_lines_and_errormessages_action);

    }

    void copySelectionToClipboard()
    {
        QStringList lines;
        QItemSelectionModel *selection = logview->selectionModel();
        QModelIndexList rows = selection->selectedRows();
        qSort(rows);
        foreach(QModelIndex index, rows)
        {
            lines << logview->model()->data(index).toString();
        }
        QApplication::clipboard()->setText(lines.join("\n"));
        qDebug() << "Copies selected";
    }

public slots:

    void selectAllEntries()
    {
        qDebug() << "Selects all lines";
    }

    void selectTheSuccessfullEntries()
    {
        qDebug() << "Selects the successfull lines";
    }

    void selectTheFailedEntries()
    {
        qDebug() << "Selects the failed lines";
    }

    void selectTheFailedEntriesAndErrorMessages()
    {
        qDebug() << "Selects the failed lines AND their errormessages";
    }

};

#include "LogView.moc"


LogView::LogView(QWidget *parent) :
    QTreeView(parent)
{
    d = new LogViewPrivate(this);
}

LogView::~LogView()
{

}

void LogView::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_C ) && (event->modifiers() & Qt::ControlModifier))
    {
        d->copySelectionToClipboard();
        return;
    }
    QTreeView::keyPressEvent(event);

}

void LogView::contextMenuEvent(QContextMenuEvent *cme)
{

    d->contextmenu.popup(mapToGlobal(cme->pos()));
}
