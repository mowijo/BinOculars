#ifndef TESTDATABASEPROVIDER_H
#define TESTDATABASEPROVIDER_H

#include <QObject>
#include <QStringList>

class TestDataBaseProvider : public QObject
{
    Q_OBJECT

public:
    virtual ~TestDataBaseProvider();
    QString createTestDataBaseOnDiskFromString(const QString &filename);

private:
    QStringList temporaryfiles;
    
};

#endif // TESTDATABASEPROVIDER_H
