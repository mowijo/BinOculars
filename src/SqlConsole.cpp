#include "SqlConsole.h"
#include <sqlhighlighter/src/SqlSyntaxhighLighter.h>
#include <QDebug>
#include <QKeySequence>


class HistoryStack
{
private:
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

public:
    HistoryStack()
    {
        clear();
    }

    QString previousCommand()
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

    QString nextCommand()
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

    void pushCommand(const QString &c)
    {
        history.push_back(c);
        if(history.size() > MAXSIZE) history.takeFirst();
        pointer++;
        if(pointer >= MAXSIZE) pointer = MAXSIZE - 1;
        qDebug() << "Push" << c << "Stack is " << history << "pointer is" << pointer;

    }

    void setCurrentText(const QString text)
    {
        currenttext = text;
    }

    void setHistory(QStringList h)
    {
        clear();
        foreach(QString c, h) pushCommand(c);
    }


};

class SqlConsolePrivate : public QObject
{
    Q_OBJECT

private:
    SqlConsole *p;

public:

    SqlSyntaxhighLighter shl;
    HistoryStack history;

    SqlConsolePrivate(SqlConsole *parent) : QObject(parent)
    {
        p = parent;
    }

};

#include "SqlConsole.moc"

SqlConsole::SqlConsole(QWidget *parent) :
    QPlainTextEdit(parent)
{
    d = new SqlConsolePrivate(this);
    setFont(QFont("courier"));

    //d->shl.setDocument(document());
}

SqlConsole::~SqlConsole()
{
}


void SqlConsole::setHistory(const QStringList &history)
{
    d->history.setHistory(history);
}

void SqlConsole::keyPressEvent(QKeyEvent *e)
{

    if((e->key() == Qt::Key_Return) && (e->modifiers() & Qt::ControlModifier))
    {
        if(this->toPlainText() != "")
        {
            d->history.pushCommand(this->toPlainText());
            emit triggered(this->toPlainText());
        }
        return;
    }
    if((e->key() == Qt::Key_Tab) && (e->modifiers() & Qt::ControlModifier))
    {
        emit databaseSelectorKeyTriggered();
        e->accept();
        return;
    }
    if((e->key() == Qt::Key_Up) && (e->modifiers() & Qt::ControlModifier))
    {
        QString prevcommand = d->history.previousCommand();
        if(prevcommand != "") setPlainText(prevcommand);
        e->accept();
        return;
    }
    if((e->key() == Qt::Key_Down) && (e->modifiers() & Qt::ControlModifier))
    {
        setPlainText(d->history.nextCommand());
        e->accept();
        return;
    }

    //Then the user is probably typing something...
    //Let's remember that for the history.
    d->history.setCurrentText(this->toPlainText());

    QPlainTextEdit::keyPressEvent(e);
}
