#include "Column.h"
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

class ColumnPrivate
{
private:
    Column *p;

public:

    int id;
    QString name;
    QString type;
    bool notnull;
    QString dflt_value;
    bool primarykey;

    ColumnPrivate(Column *p)
    {
        this->p = p;
    }

    void deepCopy(ColumnPrivate *other)
    {
        id = other->id;
        name = other->name;
        type = other->type;
        notnull = other->notnull;
        dflt_value = other->dflt_value;
        primarykey = other->primarykey;
    }
};

Column::Column()
{
    d = new ColumnPrivate(this);
}


Column::Column(const Column &other)
{
    d = new ColumnPrivate(this);
    d->deepCopy(other.d);
}

Column &Column::operator ==(const Column &other)
{
    if(this == &other) return *this;
    d->deepCopy(other.d);
    return *this;
}

Column::~Column()
{
    delete d;
}

int Column::id() const
{
    return d->id;
}

QString Column::name() const
{
    return d->name;
}

QString Column::type() const
{
    return d->type;
}

bool Column::notNull() const
{
    return d->notnull;
}

QString Column::dfltValue() const
{
    return d->dflt_value;
}

bool Column::primaryKey() const
{
    return d->primarykey;
}

void Column::setId(int id)
{
    d->id = id;
}

void Column::setName(QString name)
{
    d->name = name;
}

void Column::setType(QString type)
{
    d->type = type;
}

void Column::setNotNull(bool nn)
{
    d->notnull = nn;
}

void Column::setDfltValue(QString dflt)
{
    d->dflt_value = dflt;
}

void Column::setPrimaryKey(bool pk)
{
    d->primarykey = pk;
}

