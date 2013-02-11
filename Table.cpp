#include "Table.h"
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>
#include "Column.h"
class TablePrivate
{
private:
    Table *p;

public:

    QString name;
    QString creationsql;
    QSqlDatabase *database;
    QList<Column*> columns;
    QString error;
    TablePrivate(Table *p)
    {
        this->p = p;
        database = 0;
    }

};

Table::Table(QSqlDatabase *database)
{
    d = new TablePrivate(this);
    this->setDatabase(database);
}

Table::Table(const QString name)
{
    d = new TablePrivate(this);
    d->name = name;
}

Table::Table(const QString name, const QString creationsql)
{
    d = new TablePrivate(this);
    d->name = name;
    d->creationsql = creationsql;
}

Table::~Table()
{
    delete d;
}

void Table::setDatabase(QSqlDatabase *database)
{
    d->database = database;
}

bool Table::introspect()
{
    if(d->database == 0) return false;
    QSqlQuery query = d->database->exec("PRAGMA TABLE_INFO("+d->name+");");
    while(query.next())
    {
        QString error = QObject::tr("Column '%1' missing in PRAGMA for table '%2'.");
        Column *c = new Column();
        QSqlRecord record = query.record();

        int index = record.indexOf("cid");
        if(index == -1)
        {
            d->error = error.arg("cid").arg(d->name);
            return false;
        }
        else {
            c->setId(query.value(index).toLongLong());
        }

        index = record.indexOf("name");
        if(index == -1)
        {
            d->error = error.arg("name").arg(d->name);
            return false;
        }
        else {
            c->setName(query.value(index).toString());
        }


        index = record.indexOf("type");
        if(index == -1)
        {
            d->error = error.arg("type").arg(d->name);
            return false;
        }
        else {
            c->setType(query.value(index).toString());
        }

        index = record.indexOf("notnull");
        if(index == -1)
        {
            d->error = error.arg("notnull").arg(d->name);
            return false;
        }
        else {
            c->setNotNull(query.value(index).toBool());
        }

        index = record.indexOf("dflt_value");
        if(index == -1)
        {
            d->error = error.arg("dflt_value").arg(d->name);
            return false;
        }
        else {
            c->setDfltValue(query.value(index).toString());
        }


        index = record.indexOf("pk");
        if(index == -1)
        {
            d->error = error.arg("pk").arg(d->name);
            return false;
        }
        else {
            c->setPrimaryKey(query.value(index).toBool());
        }
        d->columns << c;
    }
}

QString Table::lastError() const
{
    return d->error;
}

QString Table::name() const
{
    return d->name;
}

QString Table::creationSql() const
{
    return d->creationsql;
}

QList<Column *> Table::columns()
{
    return d->columns;
}
