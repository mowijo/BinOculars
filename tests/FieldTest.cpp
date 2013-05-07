#include "FieldTest.h"

#include <QtTest/QtTest>
#include <QString>

void FieldTest::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}
