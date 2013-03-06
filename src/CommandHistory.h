#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QString>
#include <QStringList>


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

private:
    class CommandHistoryPrivate *d;

};

#endif // COMMANDHISTORY_H
