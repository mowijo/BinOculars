#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSet>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QTableView>

#include <model/DataBase.h>
#include <model/Field.h>
#include <model/Log.h>
#include <model/LogFilter.h>

#include "CommandHistory.h"
#include "DatabaseSelector.h"
#include "FieldDialog.h"
#include "DatabaseStructureModel.h"
#include "LogDelegate.h"
#include "LogView.h"
#include "MainWindow.h"
#include "QueryResultModel.h"
#include "QuickOpenDialog.h"
#include "Settings.h"
#include "SqlConsole.h"
#include "TableView.h"

#include "ui_MainWindow.h"


namespace Gui
{


class MainWindowPrivate : public QObject
{
    Q_OBJECT

private:
    MainWindow * mainwindow;
    QList<Model::DataBase*> databases;

public:
    Ui::MainWindow *ui;
    Settings s;
    Model::DataBase *currentdatabase;
    TreeModel *dsm;
    SqlConsole *sqlconsole;
    DatabaseSelector *databaseselector;
    QSqlDatabase qdb;
    TableView resultview;
    QueryResultModel *currentresult;
    LogDelegate *logdelegate;
    LogView *logview;

    MainWindowPrivate(MainWindow *parent) : QObject(parent)
    {
        mainwindow = parent;
        ui = 0;
        currentresult = 0;
        currentdatabase = 0;
        logdelegate = 0;
    }

    ~MainWindowPrivate()
    {
        if(currentresult) delete currentresult;
        if(logdelegate) delete logdelegate;
        if(ui) delete ui;
    }

    void initializeUI()
    {
        ui = new Ui::MainWindow;
        ui->setupUi(mainwindow);
        sqlconsole = new SqlConsole;
        ui->consoleframe->layout()->addWidget(sqlconsole);
        connect(sqlconsole, SIGNAL(triggered(QString)), this, SLOT(performQueryOnActiveDatabase(QString)));
        ui->action_Recent_files->setEnabled(s.recentFiles().count() > 0);
        connect(ui->action_Recent_files, SIGNAL(triggered()), this, SLOT(openRecentFiles()));
        logview = new LogView();
        logview->setObjectName(QString::fromUtf8("logview"));
        logview->setRootIsDecorated(false);
        logview->header()->setVisible(false);
        logview->setSelectionMode(QAbstractItemView::ExtendedSelection);
        logview->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->logframe->layout()->addWidget(logview);

        QActionGroup *g = new QActionGroup(mainwindow);
        g->addAction(ui->actionBrowse);
        g->addAction(ui->actionExplore);
        g->addAction(ui->actionModify);
        g->addAction(ui->actionResult);
        g->setExclusive(true);


        QHBoxLayout *hbl = new QHBoxLayout;
        hbl->addWidget(&resultview);
        ui->queryresults->setLayout(hbl);        

        // connect actions
        connect(ui->action_Open_database, SIGNAL(triggered()), this, SLOT(selectFileToOpen()));
        connect(ui->action_Exit, SIGNAL(triggered()), mainwindow, SLOT(close()));
        connect(ui->actionCreate_New_Database, SIGNAL(triggered()), this, SLOT(createNewDataBase()));
        connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
        connect(ui->actionSql_Console, SIGNAL(triggered()), mainwindow, SLOT(focusOnSqlConsole()));
        connect(ui->actionSpawn_Result, SIGNAL(triggered()), this, SLOT(spawnResult()));
        connect(ui->actionEdit_Field, SIGNAL(triggered()), this, SLOT(editField()));

        restoreGeometries();
        disableGuiForDatabase();


    }

    void saveGeometries()
    {
        s.beginGroup("Geometries");
        s.beginGroup("MainWindow");
        s.setValue("size", mainwindow->size());
        s.setValue("position", mainwindow->pos());
        if(mainwindow->isMaximized())
        {
            s.setValue("isMaximized", mainwindow->isMaximized());
        }
        else
        {
            s.remove("isMaximized");
        }
        s.setValue("splitter", ui->mainsplitter->saveState());
        s.endGroup();
        s.beginGroup("Console");
        s.setValue("splitter", ui->console_log_splitter->saveState());
        s.endGroup();
        s.endGroup();
    }

    void restoreGeometries()
    {
        s.beginGroup("Geometries");

        s.beginGroup("MainWindow");
        if(s.contains("size")) mainwindow->resize(s.value("size").toSize());
        if(s.contains("position")) mainwindow->move(s.value("position").toPoint());
        if(s.contains("isMaximized")) mainwindow->showMaximized();
        if(s.contains("splitter")) ui->mainsplitter->restoreState(s.value("splitter").toByteArray());
        s.endGroup();

        s.beginGroup("Console");
        if(s.contains("splitter")) ui->console_log_splitter->restoreState(s.value("splitter").toByteArray());
        s.endGroup();

        s.endGroup();


    }

public slots:

    void editField()
    {
        FieldDialog fd;
        Model::Field f;
        f.setName("A name");
        f.setDfltValue("Some default");
        f.setPrimaryKey(false);
        f.setNotNullFlag(true);
        f.setType("Ged");
        fd.display(&f);
    }


    void createNewDataBase()
    {
        QString filename = QFileDialog::getSaveFileName();
        if(filename == "") return;
        Model::DataBase *newdb = Model::DataBase::createNew(filename);
        if(newdb)
        {
            setCurrentDb(newdb);
            s.addRecentFile(filename);
        }
        else
        {

        }
    }

    /** Will offer a list of recent files that are not already open*/
    void openRecentFiles()
    {

        QSet<QString> openfiles;
        foreach(Model::DataBase*db, databases)
        {
            openfiles << db->currentFileName();
        }
        QuickOpenDialog qod;
        qod.displayDoNotShowAgainSelector(false);
        qod.setFileList((QSet<QString>::fromList(s.recentFiles()) - openfiles).toList());
        if(qod.exec() != QDialog::Accepted) return;

        foreach(QString filename, qod.selectedFiles())
        {
            mainwindow->openFile(filename);
        }
    }

    void openFileActionTriggered()
    {
        QAction *a = dynamic_cast<QAction*>(sender());
        if(!a)
        {
            qFatal("%s:%d: Somebody triggered a openFileActionTriggered from an sender that was clearly not a QAction", __FILE__, __LINE__);
        }
        mainwindow->openFile(a->data().toString());
    }

    void setCurrentDb(Model::DataBase *newdb)
    {

        if(databases.indexOf(newdb) < 0)
        {
            addDatabase(newdb);
        }
        if(currentdatabase)
        {
            if(currentdatabase == newdb) return;
            s.setCommandHistoryFor(currentdatabase->currentFileName(), sqlconsole->history()->history());
        }
        currentdatabase = newdb;

        if(!dsm)
        {
            ui->actionExplore->setChecked(true);
        }
        dsm = new TreeModel(currentdatabase);
        emit mainwindow->currentDatabaseIndexChanged(databases.indexOf(newdb));
        emit mainwindow->currentDatabaseChanged(currentdatabase);
        mainwindow->setWindowTitle(QCoreApplication::applicationName()+" ["+currentdatabase->currentFileName()+"]");
        enableGuiForDatabase();
        sqlconsole->history()->setHistory(s.commandHistoryFor(newdb->currentFileName()));

        logview->setModel(newdb->filteredLog());
        if(!logdelegate)
        {
            logdelegate = new LogDelegate(newdb->log(), newdb->filteredLog(), logview);
        }
        else
        {
            logdelegate->setLog(newdb->log());
            logdelegate->setLogFilter(newdb->filteredLog());
        }
        logview->setItemDelegateForColumn(0, logdelegate);
        logview->hideColumn(1);
        logview->hideColumn(2);


    }


    void setGuiForDatabase(bool enabled)
    {
        static QList<QWidget*> widgets;
        static QList<QAction*> actions;
        if(widgets.count() == 0)
        {
            widgets << ui->viewsframe << ui->menuViews << ui->consoleframe << ui->logframe;
        }
        if(actions.count() == 0)
        {
            actions << ui->actionSql_Console  << ui->actionBrowse << ui->actionExplore << ui->actionModify
                   << ui->actionResult<< ui->actionSave_all << ui->action_Save;
        }
        foreach(QWidget *w, widgets) w->setEnabled(enabled);
        foreach(QAction *a, actions) a->setEnabled(enabled);


    }

    void enableGuiForDatabase()
    {
        setGuiForDatabase(true);
    }


    void disableGuiForDatabase()
    {
        setGuiForDatabase(false);

    }

    void setCurrentDb(int index)
    {
        qDebug() << "I set current db...";
        if(index < 0) return;
        if(index > databases.length()-1) return;
        setCurrentDb(databases[index]);
    }


    void addDatabase(Model::DataBase *db)
    {
        databases << db;
        QStringList filenames;
        foreach(Model::DataBase *d, databases)
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


    void spawnResult()
    {
        if(!currentresult) return;
        TableView *qtw = new TableView();
        QueryResultModel *qrm = currentresult->clone();
        qtw->setAttribute(Qt::WA_DeleteOnClose);
        qrm->setParent(qtw);
        qtw->setModel(qrm);
        qtw->show();

    }


    void saveAll()
    {
        qDebug() << "Save all...";
    }

    void performQueryOnActiveDatabase(const QString query)
    {

        QSqlQuery q = currentdatabase->exec(query);

        if(q.lastError().type() != QSqlError::NoError)
        {
            return;
        }

        if(currentresult)
        {
            delete currentresult;
        }
        currentresult = new QueryResultModel(q);
        resultview.setModel(currentresult);        
        ui->actionSpawn_Result->setEnabled(true);

    }

};

#include "MainWindow.moc"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    d = new MainWindowPrivate(this);
    d->initializeUI();
    d->databaseselector = new DatabaseSelector(this);
    connect(this, SIGNAL(openDataBasesChanged(QStringList)), d->databaseselector, SLOT(setDatabaseList(QStringList)));
    connect(this, SIGNAL(currentDatabaseIndexChanged(int)), d->databaseselector, SLOT(setCurrentDatabaseIndex(int)));
    connect(d->databaseselector, SIGNAL(databaseIndexSelected(int)), d, SLOT(setCurrentDb(int)));

    this->setWindowIcon(QPixmap(":/images/application-icon.png"));
    this->setWindowTitle("Captain Oates' Binoculars");

}

void MainWindow::focusOnSqlConsole()
{
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
    Model::DataBase *newdb = new Model::DataBase;
    if(!newdb->open(filename))
    {
        QMessageBox::warning(this, tr("Could not load file"), newdb->lastError());
        return false;
    }
    d->s.addRecentFile(newdb->currentFileName());
    d->setCurrentDb(newdb);
    return true;
}

} // namespace Gui
