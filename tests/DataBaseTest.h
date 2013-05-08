#ifndef DATABASETEST_H
#define DATABASETEST_H

#include <QObject>
#include "TestDataBaseProvider.h"

class DataBaseTest : public TestDataBaseProvider
{
    Q_OBJECT

private slots:
    void testLoadingSmallDatabase();
    void testAddingAndDroppingTable();

};

#endif // DATABASETEST_H
