#ifndef SQLCONSOLE_H
#define SQLCONSOLE_H

#include <QPlainTextEdit>


namespace Gui
{


class SqlConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SqlConsole(QWidget *parent = 0);
    ~SqlConsole();
    class CommandHistory * const history() const;

signals:
    void triggered(const QString &query);
    void databaseSelectorKeyTriggered();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    friend class SqlConsolePrivate;
    class SqlConsolePrivate *d;

    
};


} // namespace Gui

#endif // SQLCONSOLE_H
