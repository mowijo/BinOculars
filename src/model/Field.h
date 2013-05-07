#ifndef FIELD_H
#define FIELD_H

#include <QString>
#include <QSqlDatabase>

namespace Model
{

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
    bool isNotNullFlagSet() const;
    QString dfltValue() const;
    bool isPrimaryKey() const;

    void setId(int id);
    void setName(QString name);
    void setType(QString type);
    void setNotNullFlag(bool nn);
    void setDfltValue(QString dflt);
    void setPrimaryKey(bool pk);

        QString toCreateDefinition() const;

private:
    class FieldPrivate *d;

};

} //namespace Model

#endif // FIELD_H
