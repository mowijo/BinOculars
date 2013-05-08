#ifndef DATABASETEST_H
#define DATABASETEST_H

#include <QObject>
#include <QStringList>

class DataBaseTest : public QObject
{
    Q_OBJECT
    
private:
    QString createTestDataBaseOnDiskFromString(const QString &filename);

private slots:
    void tearDown();
    void testLoadingSmallDatabase();

private:
    QStringList temporaryfiles;
};

#endif // DATABASETEST_H
