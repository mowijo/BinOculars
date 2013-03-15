#include "LogView.h"
#include <QKeyEvent>
#include <QDebug>
#include <QClipboard>
#include <QApplication>
#include <QItemSelectionModel>

class LogViewPrivate
{

    LogView *logview;

public:
    LogViewPrivate(LogView* p)
    {
        logview = p;
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
    }

};


LogView::LogView(QWidget *parent) :
    QTreeView(parent)
{
    d = new LogViewPrivate(this);
}

LogView::~LogView()
{
    delete d;
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
