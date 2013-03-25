#include "TableView.h"
#include <QAction>
#include <QDebug>
#include <limits>
#include <QApplication>
#include <QClipboard>

namespace Gui
{

class TableViewPrivate : public QObject
{
    Q_OBJECT

private:
    TableView *tableview;

public:

    QAction *copyaction;
    QAction *copywithheaderaction;


    TableViewPrivate(TableView*p)
        : QObject(p)
    {
        tableview = p;
        copyaction = new QAction("Copy", tableview);
        copyaction->setShortcut(QString("CTRL+C"));
        tableview->addAction(copyaction);

        copywithheaderaction = new QAction("Copy With Column Names", tableview);
        copywithheaderaction->setShortcut(QString("CTRL+SHIFT+C"));
        tableview->addAction(copywithheaderaction);

        connect(copyaction, SIGNAL(triggered()), this, SLOT(copy()));
        connect(copywithheaderaction, SIGNAL(triggered()), this, SLOT(copyWithHeaders()));
    }

public slots:

    void copyWithHeaders()
    {
        copy(true);
    }

    void copy(bool includeheaders = false)
    {
        QAbstractItemModel *model = tableview->model();
        QItemSelectionModel *selection = tableview->selectionModel();

        QMap<int,int> fieldlengths;
        int mincol = std::numeric_limits<int>::max();
        int minrow = std::numeric_limits<int>::max();
        int maxcol = 0;
        int maxrow = 0;

        foreach(QModelIndex index, selection->selectedIndexes())
        {
            int datalength = model->data(index).toString().length();
            int maxlength = fieldlengths.value(index.column(), 0);
            if(datalength > maxlength) fieldlengths[index.column()] = datalength;

            if(index.row() < minrow) minrow = index.row();
            if(index.column() < mincol) mincol = index.column();

            if(index.row() > maxrow) maxrow = index.row();
            if(index.column() > maxcol) maxcol = index.column();
        }

        QStringList lines;

        if(includeheaders)
        {
            QString line;
            for(int c = mincol; c <= maxcol; c++)
            {
                int currentmax = fieldlengths.value(c, 0);
                int headerlength = model->headerData(c, Qt::Horizontal).toString().length();
                if(headerlength > currentmax) fieldlengths[c] = headerlength;
                line += model->headerData(c, Qt::Horizontal).toString() + "   ";

            }
            lines << line;
        }

        for(int r = minrow; r <= maxrow; r++)
        {
            QString line;
            for(int c = mincol; c <= maxcol; c++)
            {
                QString data = model->data(model->index(r,c)).toString();
                data = data.leftJustified(fieldlengths[c], ' ');
                line += data + "   ";

            }
            lines << line.trimmed();
        }
        QApplication::clipboard()->setText(lines.join("\n"));

    }

};

#include "TableView.moc"

TableView::TableView(QWidget *parent) :
    QTableView(parent)
{
    d = new TableViewPrivate(this);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
}

} // namespace Gui
