#include "Field.h"
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QDebug>

class FieldPrivate
{
private:
    Field *p;

public:

    int id;
    QString name;
    QString type;
    bool notnull;
    QString dflt_value;
    bool primarykey;

    FieldPrivate(Field *p)
    {
        this->p = p;
    }

    void deepCopy(FieldPrivate *other)
    {
        id = other->id;
        name = other->name;
        type = other->type;
        notnull = other->notnull;
        dflt_value = other->dflt_value;
        primarykey = other->primarykey;
    }
};

Field::Field()
{
    d = new FieldPrivate(this);
}


Field::Field(const Field &other)
{
    d = new FieldPrivate(this);
    d->deepCopy(other.d);
}

Field &Field::operator ==(const Field &other)
{
    if(this == &other) return *this;
    d->deepCopy(other.d);
    return *this;
}

Field::~Field()
{
    delete d;
}

int Field::id() const
{
    return d->id;
}

QString Field::name() const
{
    return d->name;
}

QString Field::type() const
{
    return d->type;
}

bool Field::notNull() const
{
    return d->notnull;
}

QString Field::dfltValue() const
{
    return d->dflt_value;
}

bool Field::primaryKey() const
{
    return d->primarykey;
}

void Field::setId(int id)
{
    d->id = id;
}

void Field::setName(QString name)
{
    d->name = name;
}

void Field::setType(QString type)
{
    d->type = type;
}

void Field::setNotNull(bool nn)
{
    d->notnull = nn;
}

void Field::setDfltValue(QString dflt)
{
    d->dflt_value = dflt;
}

void Field::setPrimaryKey(bool pk)
{
    d->primarykey = pk;
}
