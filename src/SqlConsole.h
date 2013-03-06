#ifndef SQLCONSOLE_H
#define SQLCONSOLE_H

#include <QPlainTextEdit>

class SqlConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SqlConsole(QWidget *parent = 0);
    ~SqlConsole();
    void setHistory(const QStringList &history);

signals:
    void triggered(const QString &query);
    void databaseSelectorKeyTriggered();

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    friend class SqlConsolePrivate;
    class SqlConsolePrivate *d;

    
};

#endif // SQLCONSOLE_H
