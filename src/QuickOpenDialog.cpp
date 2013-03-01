#include "QuickOpenDialog.h"
#include "ui_QuickOpenDialog.h"

#include <QStringListModel>
#include <QDebug>
#include <QKeyEvent>
#include <QItemSelectionModel>

class FileListModel : public QStringListModel
{
    Qt::ItemFlags flags ( const QModelIndex & index ) const
    {
        return Qt::ItemIsSelectable | Qt:: ItemIsEnabled;
    }
};



class QuickOpenDialogPrivate : public QObject
{

    Q_OBJECT

private:
    QuickOpenDialog *p;
public:

    Ui::QuickOpenDialog *ui;

    QuickOpenDialogPrivate(QuickOpenDialog *p) : QObject(p)
    {
        ui = new Ui::QuickOpenDialog;
        this->p = p;
    }

    ~QuickOpenDialogPrivate()
    {
        delete ui;
    }


};

#include "QuickOpenDialog.moc"

QuickOpenDialog::QuickOpenDialog(QWidget *parent) :
    QDialog(parent)
{
    d = new QuickOpenDialogPrivate(this);
    d->ui->setupUi(this);
    d->ui->list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(d->ui->closebutton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(d->ui->openbutton, SIGNAL(clicked()), this, SLOT(accept()));

    connect(d->ui->list, SIGNAL(activated(QModelIndex)), this, SLOT(accept()));
    connect(d->ui->list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));

}

QuickOpenDialog::~QuickOpenDialog()
{    

}

void QuickOpenDialog::setFileList(QStringList files)
{
    QStringListModel *qslm = new FileListModel();
    qslm->setStringList(files);
    d->ui->list->setModel(qslm);
}

QStringList QuickOpenDialog::selectedFiles() const
{
    QStringList selected;
    if(!d->ui->list->selectionModel()) return selected;

    foreach(QModelIndex index, d->ui->list->selectionModel()->selectedRows())
    {
        selected << d->ui->list->model()->data(index).toString();
    }
    return selected;
}

void QuickOpenDialog::keyPressEvent(QKeyEvent *ke)
{
    if(ke->key() == Qt::Key_Escape)
    {
        ke->accept();
        reject();
        return;
    }
    ke->ignore();
}

void QuickOpenDialog::displayDoNotShowAgainSelector(bool show)
{
    d->ui->memorylabel->hide();
}
