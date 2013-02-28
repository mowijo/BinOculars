#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QuickOpenDialog.h"
#include "Settings.h"
#include "DataBase.h"
#include "DatabaseStructureModel.h"
#include "SqlConsole.h"
#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "GlobalEventFilter.h"

class MainWindowPrivate : public QObject
{
    Q_OBJECT

private:
    MainWindow * mainwindow;
    QList<DataBase*> databases;

public:
    Ui::MainWindow *ui;
    Settings s;
    DataBase *currentdatabase;
    TreeModel *dsm;
    SqlConsole *sqlconsole;
    GlobalEventFilter *globaleventfilter;


    MainWindowPrivate(MainWindow *parent) : QObject(parent)
    {
        mainwindow = parent;
        ui = 0;
    }

    ~MainWindowPrivate()
    {
        if(ui) delete ui;
    }

    void initializeUI()
    {
        ui = new Ui::MainWindow;
        ui->setupUi(mainwindow);
        sqlconsole = new SqlConsole;
        QVBoxLayout *vbl = new QVBoxLayout;
        vbl->addWidget(sqlconsole);
        connect(sqlconsole, SIGNAL(triggered(QString)), this, SLOT(performQueryOnActiveDatabase(QString)));

        ui->consolegroupbox->setLayout(vbl);

        //Populate "recent files" menu
        QStringList recentfiles = s.recentFiles();

        ui->menu_Recent_files->setEnabled(recentfiles.size() > 0);

        foreach(QString recentfile, recentfiles)
        {
            QAction *a = new QAction(recentfile, this);
            a->setData(QVariant(recentfile));
            connect(a, SIGNAL(triggered()), this, SLOT(openFileActionTriggered()));
            ui->menu_Recent_files->addAction(a);
        }

        // connect actions
        connect(ui->action_Open_database, SIGNAL(triggered()), this, SLOT(selectFileToOpen()));
        connect(ui->action_Exit, SIGNAL(triggered()), mainwindow, SLOT(close()));
        connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
        connect(ui->actionSql_Console, SIGNAL(triggered()), mainwindow, SLOT(focusOnSqlConsole()));
    }

    void saveGeometries()
    {
        s.beginGroup("Geometries");
        s.beginGroup("MainWindow");
        s.setValue("size", mainwindow->size());
        s.setValue("position", mainwindow->pos());
        s.endGroup();
        s.beginGroup("Console");
        s.setValue("splitter", ui->splitter->saveState());
        s.endGroup();
        s.endGroup();
    }

    void restoreGeometries()
    {

    }

public slots:

    void openFileActionTriggered()
    {
        QAction *a = dynamic_cast<QAction*>(sender());
        if(!a)
        {
            qFatal("%s:%d: Somebody triggered a openFileActionTriggered from an sender that was clearly not a QAction", __FILE__, __LINE__);
        }
        mainwindow->openFile(a->data().toString());
    }

    void setCurrentDb(DataBase *newdb)
    {
        if(databases.indexOf(newdb) < 0)
        {
            addDatabase(newdb);
        }
        currentdatabase = newdb;
        if(dsm) delete dsm;
        dsm = new TreeModel(currentdatabase);
        ui->databaseview->setModel(dsm);
        ui->tabpane->setEnabled(true);
        ui->consoletab->setEnabled(true);
        ui->status->setEnabled(true);
        ui->result->setEnabled(true);
        ui->actionSql_Console->setEnabled(true);
        emit mainwindow->currentDatabaseIndexChanged(databases.indexOf(newdb));
        emit mainwindow->currentDatabaseChanged(currentdatabase);
        qDebug() << "Current database is" << currentdatabase->currentFileName();
    }


    void setCurrentDb(int index)
    {
        if(index < 0) return;
        if(index > databases.length()-1) return;
        setCurrentDb(databases[index]);
    }


    void addDatabase(DataBase *db)
    {
        databases << db;
        QStringList filenames;
        foreach(DataBase *d, databases)
        {
            filenames << d->currentFileName();
        }
        emit mainwindow->openDataBasesChanged(filenames);
    }


    void selectFileToOpen()
    {
        QString filename = QFileDialog::getOpenFileName(
                                mainwindow,
                                "Select a file to open",
                                s.lastOpenBrowserDirectory(),
                                "All files (*.*)");
        if(filename == "") return;
        QFileInfo fi(filename);
        s.setLastOpenBrowserDirectory(fi.absoluteDir().path());
        mainwindow->openFile(filename);
    }

    void save()
    {
        QString filename = currentdatabase->currentFileName();
        if(filename == "")
        {

        }
        if(!currentdatabase->save())
        s.addRecentFile(currentdatabase->currentFileName());

    }

    void saveAll()
    {
        qDebug() << "Save all...";
    }

    void performQueryOnActiveDatabase(const QString query)
    {

    }

};

#include "MainWindow.moc"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    d = new MainWindowPrivate(this);
    d->initializeUI();
    d->globaleventfilter = new GlobalEventFilter(this);
    connect(this, SIGNAL(openDataBasesChanged(QStringList)), d->globaleventfilter, SLOT(setDatabaseList(QStringList)));
    connect(this, SIGNAL(currentDatabaseIndexChanged(int)), d->globaleventfilter, SLOT(setCurrentDatabaseIndex(int)));
    connect(d->globaleventfilter, SIGNAL(databaseIndexSelected(int)), d, SLOT(setCurrentDb(int)));

}

void MainWindow::focusOnSqlConsole()
{
    d->ui->tabpane->setCurrentIndex(1);
    d->sqlconsole->setFocus();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    d->saveGeometries();
}

void MainWindow::showEvent(QShowEvent *)
{
}

bool MainWindow::openFile(const QString &filename)
{
    DataBase *newdb = new DataBase;
    if(!newdb->open(filename))
    {
        QMessageBox::warning(this, tr("Could not load file"), newdb->lastError());
        return false;
    }
    d->s.addRecentFile(newdb->currentFileName());
    d->setCurrentDb(newdb);
    return true;
}
