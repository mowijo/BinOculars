#include "RememberDialog.h"
#include <QDebug>

#include "Settings.h"

namespace Gui
{

RememberDialog::RememberDialog(QWidget *parent) :
    QDialog(parent)
{
}

RememberDialog::~RememberDialog()
{
}

void RememberDialog::rememberAsShouldShow(bool shouldshow) const
{
    RememberDialog::rememberAsShouldShow(metaObject()->className(), shouldshow);
}

bool RememberDialog::shouldShow() const
{
    return RememberDialog::shouldShow(metaObject()->className());
}

void RememberDialog::rememberAsShouldShow(const QString &classname, bool shouldshow)
{
    qDebug() << "I remember" << classname << "as" << shouldshow;
    Settings s;
    s.beginGroup("RememberDialogs");
    s.setValue(classname, shouldshow);
    s.endGroup();
}

bool RememberDialog::shouldShow(const QString &classname)
{
    Settings s;
    s.beginGroup("RememberDialogs");
    return s.value(classname, true).toBool();

}

} // namespace Gui
