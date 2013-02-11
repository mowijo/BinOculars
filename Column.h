#ifndef COLUMN_H
#define COLUMN_H

#include <QString>
#include <QSqlDatabase>

class Column
{
public:
    Column();
    Column(const Column &other);
    Column &operator==(const Column &other);
    ~Column();

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
    class ColumnPrivate *d;

};



#endif // COLUMN_H
