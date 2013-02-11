#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QSqlDatabase>
#include <QList>

class Column;
class Table
{
public:
    Table(QSqlDatabase *database);
    Table(const QString name);
    Table(const QString name, const QString creationsql);
    ~Table();

    void setDatabase(QSqlDatabase *database);
    bool introspect();
    QString lastError() const;

    QString name() const;
    QString creationSql() const;

    QList<Column*> columns();

private:
    Table(const Table &other);
    Table &operator==(const Table &other);
    class TablePrivate *d;

};



#endif // TABLE_H
