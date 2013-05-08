#include "Table.h"
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

#include "Field.h"

namespace Model
{

class TablePrivate
{
private:
    Table *p;

public:

    QString name;
    QString creationsql;
    QSqlDatabase *database;
    QList<Field*> columns;
    QString error;
    TablePrivate(Table *p)
    {
        this->p = p;
        database = 0;
    }

    bool validateFieldForAddition(const Field &field)
    {
        if(field.isPrimaryKey())
        {
            error = QObject::tr("Fields must not be primary keys.");
            return false;
        }
        if( (field.dfltValue().toUpper() == "CURRENT_TIME")
                || (field.dfltValue().toUpper() == "CURRENT_DATE")
                || (field.dfltValue().toUpper() == "CURRENT_TIMESTAMP")
                )
        {
            error = QObject::tr("Default value when adding a fiels may not be any of %1.").arg("CURRENT_TIME, CURRENT_DATE, CURRENT_TIMESTAMP");
            return false;
        }
        if((field.dfltValue().trimmed()[0] == '(') && field.dfltValue().trimmed()[field.dfltValue().trimmed().length()-1] == ')')
        {
            error = QObject::tr("Default value when adding a column must not me an expression in paranthesis.");
            return false;
        }
        if(field.isNotNullFlagSet())
        {
            if ((field.dfltValue().trimmed().toUpper() == "NULL")
                ||
                (field.dfltValue().trimmed() == ""))
            {
                error = QObject::tr("When adding a field marked as NOT NULL the default value must be a non NULL value.");
                return false;
            }
        }
        if(field.name().trimmed() == "")
        {
            error = QObject::tr("A field must have a name in order to be added.");
            return false;
        }
        if(field.type().trimmed() == "")
        {
            error = QObject::tr("A field must have a type in order to be added.");
            return false;
        }
        return true;
    }


};

Table::Table()
{
    d = new TablePrivate(this);
}

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
    if(d->database == 0)
    {
        d->error = QObject::tr("No database has been set on the table, why the it cannot introspect itself.");
        return false;
    }
    QSqlQuery query = d->database->exec("PRAGMA TABLE_INFO("+d->name+");");
    while(query.next())
    {
        QString error = QObject::tr("Column '%1' missing in PRAGMA for table '%2'.");
        Field *c = new Field();
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
            c->setNotNullFlag(query.value(index).toBool());
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
    return true;
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

QList<Field *> Table::columns()
{
    return d->columns;
}


/**
* The column may not have a PRIMARY KEY or UNIQUE constraint.
* The column may not have a default value of CURRENT_TIME, CURRENT_DATE, CURRENT_TIMESTAMP, or an expression in parentheses.
* If a NOT NULL constraint is specified, then the column must have a default value other than NULL.
* If foreign key constraints are enabled and a column with a REFERENCES clause is added, the column must have a default value of NULL.
  */
bool Table::addField(const Field &field, int position)
{
    if(!d->validateFieldForAddition(field)) return false;
    return true;
}

bool Table::removeField(int position)
{
    return true;
}

bool Table::moveField(int current_position, int new_position)
{
    return true;
}

} // namespace Model
