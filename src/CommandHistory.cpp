#include "CommandHistory.h"

#include <QDebug>

void CommandHistory::clear()
{
    pointer = -1;
    MAXSIZE = 5;
    history.clear();
    currenttext = "";
}


CommandHistory::CommandHistory()
{
    clear();
}

QString CommandHistory::previousCommand()
{
    int pointerbefore = pointer;
    QString r;
    if(pointer >= history.size())
    {
        pointer = history.size()-1;
    }
    if(pointer < 0)
    {
        r = "";
    }
    else
    {
        r = history.at(pointer);
        pointer--;
    }
    qDebug() << "I return " << r << "Stack is " << history << "pointer was" << pointerbefore << "pointer is" << pointer;
    return r;
}

QString CommandHistory::nextCommand()
{
    int pointerbefore = pointer;
    QString r;
    if(pointer < 0)
    {
        pointer = 1;
    }
    if(pointer >= history.size())
    {
        r = currenttext;
    }
    else
    {
        r = history.at(pointer);
        pointer++;
    }
    qDebug() << "I return " << r << "Stack is " << history << "pointer was" << pointerbefore << "pointer is" << pointer;
    return r;
}

void CommandHistory::pushCommand(const QString &c)
{
    history.push_back(c);
    if(history.size() > MAXSIZE) history.takeFirst();
    pointer++;
    if(pointer >= MAXSIZE) pointer = MAXSIZE - 1;
    qDebug() << "Push" << c << "Stack is " << history << "pointer is" << pointer;

}

void CommandHistory::setCurrentText(const QString text)
{
    currenttext = text;
}

void CommandHistory::setHistory(QStringList h)
{
    clear();
    foreach(QString c, h) pushCommand(c);
}

