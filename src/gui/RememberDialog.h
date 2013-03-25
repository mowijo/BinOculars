#ifndef REMEMBERDIALOG_H
#define REMEMBERDIALOG_H

#include <QDialog>


namespace Gui
{


class RememberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RememberDialog(QWidget *parent = 0);
    virtual ~RememberDialog();
    void rememberAsShouldShow(bool shouldshow) const;
    bool shouldShow() const;

    virtual QString rememberDialogLabel() const = 0;
    virtual QString rememberDialogDescription() const = 0;

    static void rememberAsShouldShow(const QString &classname, bool shouldshow);
    static bool shouldShow(const QString &classname);


};

} // namespace Gui

#endif // REMEMBERDIALOG_H
