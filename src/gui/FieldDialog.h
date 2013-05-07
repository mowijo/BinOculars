#ifndef FIELDDIALOG_H
#define FIELDDIALOG_H

#include <QDialog>

namespace Model
{
    class Field;
}

class FieldDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FieldDialog(QWidget *parent = 0);
    int display(Model::Field *field);

private:
    friend class FieldDialogPrivate;
    class FieldDialogPrivate *d;

};

#endif // FIELDDIALOG_H
