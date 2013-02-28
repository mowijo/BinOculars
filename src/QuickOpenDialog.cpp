#include "QuickOpenDialog.h"
#include "ui_QuickOpenDialog.h"

#include <QStringListModel>
#include <QDebug>
#include <QKeyEvent>
#include <QItemSelectionModel>

class QuickOpenDialogPrivate : QObject
{

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

public slots:

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
}

QuickOpenDialog::~QuickOpenDialog()
{    

}

void QuickOpenDialog::setFileList(QStringList files)
{
    QStringListModel *qslm = new QStringListModel();
    qslm->setStringList(files);
    d->ui->list->setModel(qslm);
}

QStringList QuickOpenDialog::selectedFiles() const
{
    QStringList selected;
    foreach(QModelIndex index, d->ui->list->selectionModel()->selectedRows())
    {
        selected << d->ui->list->model()->data(index).toString();
    }
    return selected;
}

void QuickOpenDialog::keyPressEvent(QKeyEvent *ke)
{
    if((ke->key() == Qt::Key_Return) && (ke->modifiers() && Qt::ControlModifier))
    {
        ke->accept();
        accept();
    }
    ke->ignore();
}
