#include "LogView.h"
#include <QKeyEvent>
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QAbstractItemModel>
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
    QAction *deselect_everything;
    QAction *copy_selection_to_clipboard_action;

    QMenu contextmenu;

    LogViewPrivate(LogView* p) : QObject(p)
    {
        logview = p;

        copy_selection_to_clipboard_action = new QAction(tr("Copy selection"), p);
        copy_selection_to_clipboard_action->setShortcut(QKeySequence("CTRL+C"));
        copy_selection_to_clipboard_action->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(copy_selection_to_clipboard_action);
        connect(copy_selection_to_clipboard_action, SIGNAL(triggered()), this, SLOT(copySelectionToClipboard()));


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

        deselect_everything = new QAction(tr("Clear selection"), p);
        deselect_everything->setShortcut(QKeySequence("CTRL+A,CTRL+N"));
        deselect_everything->setShortcutContext(Qt::WidgetShortcut);
        p->addAction(deselect_everything);
        connect(deselect_everything, SIGNAL(triggered()), this, SLOT(clearSelection()));

        contextmenu.addAction(select_all_lines_action);
        contextmenu.addAction(select_successfull_lines_action);
        contextmenu.addAction(select_failed_lines_action);
        contextmenu.addAction(select_failed_lines_and_errormessages_action);
        contextmenu.addAction(deselect_everything);
        contextmenu.addSeparator();
        contextmenu.addAction(copy_selection_to_clipboard_action);
        updateSelectionDependendActions();
        updateSelectActions();
    }

public slots:

    void updateSelectActions()
    {
        if(!logview->model() || (logview->model()->rowCount() == 0))
        {
            select_all_lines_action->setEnabled(false);
            select_successfull_lines_action->setEnabled(false);
            select_failed_lines_action->setEnabled(false);
            select_failed_lines_and_errormessages_action->setEnabled(false);
            return;
        }
    }

    void updateSelectionDependendActions()
    {
        QItemSelectionModel *selection = logview->selectionModel();
        if(!selection)
        {
            copy_selection_to_clipboard_action->setEnabled(false);
            deselect_everything->setEnabled(false);

        }
        else if(selection->selectedIndexes().size() == 0)
        {
            copy_selection_to_clipboard_action->setEnabled(false);
            deselect_everything->setEnabled(false);
        }
        else
        {
            copy_selection_to_clipboard_action->setEnabled(true);
            deselect_everything->setEnabled(true);
        }

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

    void selectAllEntries()
    {
        qDebug() << "Selects all lines";
    }

    void clearSelection()
    {
        QItemSelectionModel *selectionmodel = logview->selectionModel();
        if(!selectionmodel) return;
        selectionmodel->clearSelection();
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

void LogView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);
    connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), d, SLOT(updateSelectionDependendActions()));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(updateSelectActions()));
    connect(model, SIGNAL(rowsInserted ( const QModelIndex & , int , int )), d, SLOT(updateSelectActions()));
    connect(model, SIGNAL(rowsRemoved ( const QModelIndex & , int , int )), d, SLOT(updateSelectActions()));
    connect(model, SIGNAL(modelReset ()), d, SLOT(updateSelectActions()));
    connect(model, SIGNAL(columnsRemoved ( const QModelIndex & , int , int )), d, SLOT(updateSelectActions()));
    connect(model, SIGNAL(columnsInserted ( const QModelIndex & , int, int )), d, SLOT(updateSelectActions()));


}
void LogView::contextMenuEvent(QContextMenuEvent *cme)
{

    d->contextmenu.popup(mapToGlobal(cme->pos()));
}

