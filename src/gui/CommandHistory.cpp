#include "CommandHistory.h"

#include <QDebug>

class CommandHistoryPrivate
{

public:

    int pointer;
    QStringList history;
    QString currenttext;
    int MAXSIZE;

    void clear()
    {
        pointer = -1;
        MAXSIZE = 5;
        history.clear();
        currenttext = "";
    }


};




CommandHistory::CommandHistory()
{
    d = new CommandHistoryPrivate;
    d->clear();
}

CommandHistory::~CommandHistory()
{
    delete d;
}

QString CommandHistory::previousCommand()
{
    QString r;
    if(d->pointer >= d->history.size())
    {
        d->pointer = d->history.size()-1;
    }
    if(d->pointer < 0)
    {
        r = "";
    }
    else
    {
        r = d->history.at(d->pointer);
        d->pointer--;
    }
    //qDebug() << "I return " << r << "Stack is " << d->history << "pointer was" << pointerbefore << "pointer is" << d->pointer;
    return r;
}

QString CommandHistory::nextCommand()
{

    QString r;
    if(d->pointer < 0)
    {
        d->pointer = 1;
    }
    if(d->pointer >= d->history.size())
    {
        r = d->currenttext;
    }
    else
    {
        r = d->history.at(d->pointer);
        d->pointer++;
    }
    //qDebug() << "I return " << r << "Stack is " << d->history << "pointer was" << pointerbefore << "pointer is" << d->pointer;
    return r;
}


/**
@note Will not push empty strings or strings consisting of white spaces only.
@note Will not push a command if it is equal to the command on the top of the stack.
*/
void CommandHistory::pushCommand(const QString &c)
{
    if(c.trimmed() == "") return;
    if(d->history.size() > 0)
    {
        if(c == d->history.last()) return;
    }
    d->history.push_back(c);
    if(d->history.size() > d->MAXSIZE) d->history.takeFirst();
    d->pointer++;
    if(d->pointer >= d->MAXSIZE) d->pointer = d->MAXSIZE - 1;
    //qDebug() << "Push" << c << "Stack is " << d->history << "pointer is" << d->pointer;

}

void CommandHistory::setCurrentText(const QString text)
{
    d->currenttext = text;
}

void CommandHistory::setHistory(QStringList h)
{
    d->clear();
    foreach(QString c, h) pushCommand(c);
}

QStringList CommandHistory::history() const
{
    return d->history;
}

