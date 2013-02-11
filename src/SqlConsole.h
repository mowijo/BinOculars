#ifndef SQLCONSOLE_H
#define SQLCONSOLE_H

#include <QPlainTextEdit>

class SqlConsole : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit SqlConsole(QWidget *parent = 0);
    ~SqlConsole();
    
signals:
    void triggered(const QString &query);
    
protected:
    void keyPressEvent(QKeyEvent *e);

private:
    friend class SqlConsolePrivate;
    class SqlConsolePrivate *d;

    
};

#endif // SQLCONSOLE_H
