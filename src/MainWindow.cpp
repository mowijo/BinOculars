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

class MainWindowPrivate : public QObject
{
    Q_OBJECT

private:
    MainWindow * p;

public:
    Ui::MainWindow *ui;
    Settings s;
    DataBase *db;
    TreeModel *dsm;
    SqlConsole *sqlconsole;

    MainWindowPrivate(MainWindow *parent) : QObject(parent)
    {
        p = parent;
        ui = 0;
    }

    ~MainWindowPrivate()
    {
        if(ui) delete ui;
    }

    void initializeUI()
    {
        ui = new Ui::MainWindow;
        ui->setupUi(p);
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
        connect(ui->action_Exit, SIGNAL(triggered()), p, SLOT(close()));
        connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
        connect(ui->actionSql_Console, SIGNAL(triggered()), p, SLOT(focusOnSqlConsole()));
    }

    void saveGeometries()
    {
        s.beginGroup("Geometries");
        s.beginGroup("MainWindow");
        s.setValue("size", p->size());
        s.setValue("position", p->pos());
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
        openFile(a->data().toString());
    }

    void setCurrentDb(DataBase *newdb)
    {
        db = newdb;
        if(dsm) delete dsm;
        dsm = new TreeModel(db);
        ui->databaseview->setModel(dsm);
        ui->tabpane->setEnabled(true);
        ui->consoletab->setEnabled(true);
        ui->status->setEnabled(true);
        ui->result->setEnabled(true);
        ui->actionSql_Console->setEnabled(true);
    }


    void openFile(const QString &filename)
    {
        DataBase *newdb = new DataBase;
        if(!newdb->open(filename))
        {
            QMessageBox::warning(p, tr("Could not load file"), newdb->lastError());
            qDebug() << "Could not open file " << newdb->lastError();
            return;
        }
        s.addRecentFile(newdb->currentFileName());
        setCurrentDb(newdb);
    }

    void selectFileToOpen()
    {
        QString filename = QFileDialog::getOpenFileName(
                                p,
                                "Select a file to open",
                                s.lastOpenBrowserDirectory(),
                                "All files (*.*)");
        if(filename == "") return;
        QFileInfo fi(filename);
        s.setLastOpenBrowserDirectory(fi.absoluteDir().path());
        openFile(filename);
    }

    void save()
    {
        QString filename = db->currentFileName();
        if(filename == "")
        {

        }
        if(!db->save())
        s.addRecentFile(db->currentFileName());

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

