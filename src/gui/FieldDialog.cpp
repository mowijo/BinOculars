#include "FieldDialog.h"
#include "ui_FieldDialog.h"
#include <QShortcut>
#include <model/Field.h>

class FieldDialogPrivate : public QObject
{
    Q_OBJECT

private:
    FieldDialog *fielddialog;

public:
    Ui::FieldDialog *ui;
    Model::Field *displayed_field ;

    FieldDialogPrivate(FieldDialog *parent)
        : QObject(parent)
    {
        fielddialog = parent;
        displayed_field = 0;
        ui = new Ui::FieldDialog;
        ui->setupUi(parent);
        new QShortcut(QKeySequence("RETURN"), parent, SLOT(accept()));
        connect(parent, SIGNAL(rejected()), this, SLOT(reject()));
        connect(parent, SIGNAL(accepted()), this, SLOT(accept()));
        connect(ui->cancel_button, SIGNAL(clicked()), parent, SLOT(reject()));
        connect(ui->ok_button, SIGNAL(clicked()), parent, SLOT(accept()));
        reTranslate();
    }

    ~FieldDialogPrivate()
    {
        delete ui;
    }

public slots:

    void reTranslate()
    {
        ui->group_box->setTitle(tr("Field Details"));
        ui->name_label->setText(tr("&Name:"));
        ui->type_label->setText(tr("&Type:"));
        ui->null_label->setText(tr("NOT &NULL:"));
        ui->primary_key_label->setText(tr("&PRIMARY KEY:"));
        ui->dflt_label->setText(tr("&DEFAULT:"));
        ui->ok_button->setText(tr("&OK"));
        ui->cancel_button->setText(tr("&Cancel"));
    }

    void cleanUp()
    {
        displayed_field = 0;
    }

    void reject()
    {
        cleanUp();
        qDebug("Handles a reject");
    }

    void accept()
    {
        cleanUp();
        qDebug("Handles an accept");
    }

};

#include "FieldDialog.moc"

FieldDialog::FieldDialog(QWidget *parent) :
    QDialog(parent)

{
    d = new FieldDialogPrivate(this);
}

int FieldDialog::display(Model::Field *field)
{
    d->ui->name_edit->setText(field->name());
    d->ui->dflt_edit->setText(field->dfltValue());
    d->ui->null_box->setChecked(field->isNotNullFlagSet());
    d->ui->pk_box->setChecked(field->isPrimaryKey());
    if(!d->ui->type_edit->lineEdit())
    {
        qFatal("Jackass. The type combo needs to be editable. Doooh: %s %d", __FILE__, __LINE__);
    }
    d->ui->type_edit->lineEdit()->setText(field->type());
    d->displayed_field = field;
    return exec();
}




