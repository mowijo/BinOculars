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
    Table();
    explicit Table(QSqlDatabase *database);
    explicit Table(const QString name);
    Table(const QString name, const QString creationsql);
    ~Table();

    void setDatabase(QSqlDatabase *database);
    bool introspect();
    QString lastError() const;

    QString name() const;
    QString creationSql() const;

    QList<Field*> columns();
    bool addField(const Field &field, int position = -1);
    bool removeField(int position);
    bool moveField(int current_position, int new_position);

private:
    Table(const Table &other);  //Do not implement!
    Table &operator=(const Table &other); //Do not implement!
    class TablePrivate *d;

};

} // namespace Model

#endif // TABLE_H
