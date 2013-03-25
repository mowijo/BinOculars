#include "SqlConsole.h"
#include <sqlhighlighter/src/SqlSyntaxhighLighter.h>
#include <QDebug>
#include <QKeySequence>
#include "CommandHistory.h"

namespace Gui
{

class SqlConsolePrivate : public QObject
{
    Q_OBJECT

private:
    SqlConsole *p;

public:

    SqlSyntaxhighLighter shl;
    CommandHistory history;

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

    d->shl.setDocument(document());
}

SqlConsole::~SqlConsole()
{
}

CommandHistory * const SqlConsole::history() const
{
    return &d->history;
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

} // namespace Gui
