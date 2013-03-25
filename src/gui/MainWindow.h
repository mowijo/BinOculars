#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

namespace Model
{
    class DataBase;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);


    bool openFile(const QString &filename);

public slots:
    void focusOnSqlConsole();

protected:
    void closeEvent(class QCloseEvent *);
    void showEvent(QShowEvent *);

signals:
    void currentDatabaseChanged(Model::DataBase *db);
    void currentDatabaseIndexChanged(int);
    void openDataBasesChanged(const QStringList &filenames);




private:
    class MainWindowPrivate *d;
    friend class MainWindowPrivate;
};

#endif // MAINWINDOW_H
