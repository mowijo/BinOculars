#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QList>
#include <QSqlQuery>

namespace Model
{

class Table;
class FilteredLog;
class Log;

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    static DataBase * createNew(const QString &filename);
    virtual ~DataBase();

    bool open(const QString &filename);
    QString currentFileName() const;
    bool save(const QString &filename = "");
    QString lastError() const;
    QList<Table*> tables();
    QSqlQuery exec(const QString &query);


    FilteredLog* filteredLog() const;
    Log* log() const;

private:
    DataBase(const DataBase &other);
    DataBase& operator==(const DataBase &other);
    class DataBasePrivate *d;
    friend class DataBasePrivte;

};

} //namespace Model
#endif // DATABASE_H
