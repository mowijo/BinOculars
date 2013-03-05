#include "SqlConsole.h"
#include <sqlhighlighter/src/SqlSyntaxhighLighter.h>
#include <QDebug>
#include <QKeySequence>

class SqlConsolePrivate : public QObject
{
    Q_OBJECT

private:
    SqlConsole *p;

public:

    SqlSyntaxhighLighter shl;
    QStringList historystack;   //First is oldest.
    int historystackpointer;
    int MAXSTACKSIZE;
    QString historycurrenttext;

    SqlConsolePrivate(SqlConsole *parent) : QObject(parent)
    {
        p = parent;
        historystackpointer = -1;
        MAXSTACKSIZE = 5;
    }

    void pushCommandOnHistoryStack(const QString &text)
    {
        if(text == historystack.last()) return;
        historystack.append(text);
        if(historystack.size() > MAXSTACKSIZE)
        {
            historystack.takeFirst();
            historystackpointer = MAXSTACKSIZE;
        }
        else
        {
            historystackpointer++;
        }
    }


    QString moveStackPointerTowardsOlder(int step = 1)
    {
        historystackpointer -= step;
        if(historystackpointer < 0) historystackpointer = 0;
        return historystack[historystackpointer];
    }

    QString moveStackPointerTowardsNewer(int step = 1)
    {
        if(historystackpointer >= historystack.size()-1) return historycurrenttext;
        historystackpointer += step;
        if(historystackpointer >= historystack.size()) historystackpointer = historystack.size()-1;
        return historystack[historystackpointer];
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

void SqlConsole::keyPressEvent(QKeyEvent *e)
{

    if((e->key() == Qt::Key_Return) && (e->modifiers() & Qt::ControlModifier))
    {
        emit triggered(this->toPlainText());
        d->pushCommandOnHistoryStack(this->toPlainText());
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
        setPlainText(d->moveStackPointerTowardsOlder());
        e->accept();
        return;
    }
    if((e->key() == Qt::Key_Down) && (e->modifiers() & Qt::ControlModifier))
    {
        setPlainText(d->moveStackPointerTowardsNewer());
        e->accept();
        return;
    }

    //Then the user is probably typing something...
    //Let's remember that for the history.
    d->historycurrenttext = toPlainText();

    QPlainTextEdit::keyPressEvent(e);
}
