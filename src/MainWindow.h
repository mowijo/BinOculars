#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

public slots:
    void focusOnSqlConsole();
private:
    class MainWindowPrivate *d;
};

#endif // MAINWINDOW_H
