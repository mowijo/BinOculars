#ifndef QUICKOPENDIALOG_H
#define QUICKOPENDIALOG_H

#include <QDialog>
#include <QStringList>
#include "RememberDialog.h"


namespace Gui
{


class QuickOpenDialog : public RememberDialog
{
    Q_OBJECT
    
public:
    explicit QuickOpenDialog(QWidget *parent = 0);
    ~QuickOpenDialog();
    void setFileList(QStringList files);
    QStringList selectedFiles() const;
    bool shouldIgnoreNextTime() const;
    void displayDoNotShowAgainSelector(bool show);

    QString rememberDialogLabel() const;
    QString rememberDialogDescription() const;


protected:
    void keyPressEvent(QKeyEvent *);
    void hideEvent(QHideEvent *);

private:
    class QuickOpenDialogPrivate *d;
};


} // namespace Gui

#endif // QUICKOPENDIALOG_H
