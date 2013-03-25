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
    RememberDialog(parent)
{
    d = new QuickOpenDialogPrivate(this);
    d->ui->setupUi(this);
    d->ui->list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(d->ui->closebutton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(d->ui->openbutton, SIGNAL(clicked()), this, SLOT(accept()));

    connect(d->ui->list, SIGNAL(activated(QModelIndex)), this, SLOT(accept()));
    connect(d->ui->list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(accept()));
    d->ui->list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->ui->list->setTextElideMode(Qt::ElideMiddle);

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

void QuickOpenDialog::hideEvent(QHideEvent *)
{
    if(!d->ui->memorylabel->isHidden())
    {
        rememberAsShouldShow(!d->ui->memorylabel->isChecked());
    }
}

void QuickOpenDialog::displayDoNotShowAgainSelector(bool show)
{
    d->ui->memorylabel->hide();

}

QString QuickOpenDialog::rememberDialogLabel() const
{
    return tr("Recent Databases");
}

QString QuickOpenDialog::rememberDialogDescription() const
{
    return tr("A dialog that pops up at application launch allowing for easy access to recently opened databases.");
}
