#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QSqlDatabase>

class Field
{
public:
    Field();
    Field(const Field &other);
    Field &operator==(const Field &other);
    ~Field();

    int id() const;
    QString name() const;
    QString type() const;
    bool notNull() const;
    QString dfltValue() const;
    bool primaryKey() const;

    void setId(int id);
    void setName(QString name);
    void setType(QString type);
    void setNotNull(bool nn);
    void setDfltValue(QString dflt);
    void setPrimaryKey(bool pk);


private:
    class FieldPrivate *d;

};



#endif // FIELD_H
