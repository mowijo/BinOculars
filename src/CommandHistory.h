#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include <QString>
#include <QStringList>


class CommandHistory
{
private:
    int pointer;
    QStringList history;
    QString currenttext;
    int MAXSIZE;

    void clear();

public:
    CommandHistory();
    QString previousCommand();
    QString nextCommand();
    void pushCommand(const QString &c);
    void setCurrentText(const QString text);
    void setHistory(QStringList h);


};

#endif // COMMANDHISTORY_H
