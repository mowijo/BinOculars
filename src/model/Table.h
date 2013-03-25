#ifndef TABLE_H
#define TABLE_H

#include <QString>
#include <QSqlDatabase>
#include <QList>

namespace Model
{

class Field;
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

    QList<Field*> columns();

private:
    Table(const Table &other);
    Table &operator==(const Table &other);
    class TablePrivate *d;

};

} // namespace Model

#endif // TABLE_H
