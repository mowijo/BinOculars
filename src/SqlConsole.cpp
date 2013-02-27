#include "SqlConsole.h"
#include <sqlhighlighter/src/SqlSyntaxhighLighter.h>
#include <QDebug>

class SqlConsolePrivate : public QObject
{
    Q_OBJECT

private:
    SqlConsole *p;

public:

    SqlSyntaxhighLighter shl;

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

void SqlConsole::keyPressEvent(QKeyEvent *e)
{

    if((e->key() == Qt::Key_Return) && (e->modifiers() & Qt::ControlModifier))
    {
        emit triggered(this->toPlainText());
        return;
    }

    QPlainTextEdit::keyPressEvent(e);
}
