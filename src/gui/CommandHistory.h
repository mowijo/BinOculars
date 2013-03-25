#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QString>
#include <QStringList>


namespace Gui
{

class CommandHistory
{

public:
    CommandHistory();
    ~CommandHistory();
    QString previousCommand();
    QString nextCommand();
    void pushCommand(const QString &c);
    void setCurrentText(const QString text);
    void setHistory(QStringList h);
    QStringList history() const;

private:
    class CommandHistoryPrivate *d;

};

} //namespace Gui
#endif // COMMANDHISTORY_H
