#include "DataBase.h"
#include <QFile>
#include <QtSql>
#include "Table.h"
#include "Log.h"
#include "LogFilter.h"

class DataBasePrivate : public QObject
{
    Q_OBJECT

private:
    DataBase *p;

public:
    QString filename;
    QString error;
    QSqlDatabase connection;
    QList<Table*> tables;
    Log log;
    FilteredLog logfilter;

    DataBasePrivate(DataBase *db) : QObject(db)
    {
        p = db;
        logfilter.setLogModel(&log);
    }

    bool load(const QString &filename)
    {
        QFile f(filename);

        if(!f.exists())
        {
            error = tr("File %1 could not be found on disk.").arg(filename);
            return false;
        }

        connection = QSqlDatabase::addDatabase("QSQLITE");
        connection.setDatabaseName(filename);
        if(!connection.open())
        {
            error = connection.lastError().text();
            return false;
        }

        //First, introspect all tables.
        QSqlQuery query  = connection.exec("SELECT name, sql FROM sqlite_master where type='table'");
        if(query.lastError().type() != QSqlError::NoError)
        {
            error = query.lastError().text();
            return false;
        }
        while(query.next())
        {
            Table *t = new Table(query.value(0).toString(), query.value(1).toString());
            t->setDatabase(&connection);
            t->introspect();
            tables << t;
            qDebug() << "Introspects table" << t->name();
        }

//        //TODO
//        //Next, introcpect all indexes (whatever that may be...)
//        QSqlQuery query  = connection.exec("SELECT name, sql FROM sqlite_master where type='index'");
//        while(query.next())
//        {
//            Table *t = new Table(query.value(0).toString(), query.value(1).toString());
//            t->setDatabase(&connection);
//            t->introspect();
//            tables << t;
//            qDebug() << "Introspects table" << t->name();
//        }


//        //TODO
//        //Finally, decett how far the individual sequences have come.
//        QSqlQuery query  = connection.exec("SELECT rowid, *  FROM sqlite_sequence ORDER BY rowid");
//        while(query.next())
//        {
//            Table *t = new Table(query.value(0).toString(), query.value(1).toString());
//            t->setDatabase(&connection);
//            t->introspect();
//            tables << t;
//            qDebug() << "Introspects table" << t->name();
//        }

        this->filename = filename;
        return true;
    }

    bool save(const QString &filename)
    {
        QFile f(filename);

        if(!f.open(QFile::WriteOnly))
        {
            error = tr("Could not open file %1 for writing").arg(filename);
            return false;
        }
        this->filename = filename;
        f.close();
        return true;
    }
};

#include "DataBase.moc"

DataBase::DataBase(QObject *parent) :
    QObject(parent)
{
    d = new DataBasePrivate(this);
}

DataBase::~DataBase()
{
}


bool DataBase::open(const QString &filename)
{
    return d->load(filename);
}

QString DataBase::lastError() const
{
    return d->error;
}

QList<Table *> DataBase::tables()
{
    return d->tables;
}

QSqlQuery DataBase::exec(const QString &query)
{
    QSqlQuery q = d->connection.exec(query);
    d->log.addEntry(q);
    return q;
}

FilteredLog *DataBase::filteredLog() const
{
    return &d->logfilter;
}

bool DataBase::save(const QString &filename)
{
    if(filename == "") return d->save(d->filename);
    else return d->save(filename);
}

QString DataBase::currentFileName() const
{
    return d->filename;
}

Log *DataBase::log() const
{
    return &d->log;
}
