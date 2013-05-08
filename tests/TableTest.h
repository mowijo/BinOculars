#ifndef TABLETEST_H
#define TABLETEST_H

#include <QObject>
#include "TestDataBaseProvider.h"

class TableTest : public TestDataBaseProvider
{
    Q_OBJECT

private slots:
    void testConstructors();
    void testNonWorkingIntrospect();
    void testAddInvalidField();
    void testAddField();
};

#endif // TABLETEST_H
