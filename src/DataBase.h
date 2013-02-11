#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QList>

class Table;

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = 0);
    virtual ~DataBase();

    bool open(const QString &filename);
    QString currentFileName() const;
    bool save(const QString &filename = "");
    QString lastError() const;
    QList<Table*> tables();
    
signals:
    
public slots:

private:
    DataBase(const DataBase &other);
    DataBase& operator==(const DataBase &other);
    class DataBasePrivate *d;
    friend class DataBasePrivte;

};

#endif // DATABASE_H
