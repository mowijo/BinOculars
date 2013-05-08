#include "TableTest.h"
#include <model/Table.h>
#include <QtTest/QtTest>

void TableTest::testConstructors()
{
    {
        Model::Table t;
        QCOMPARE(QString(""), t.name());
        QCOMPARE(QString(""), t.creationSql());
        QCOMPARE(QString(""), t.lastError());
        QCOMPARE(0, t.columns().size());
    }
    {
        Model::Table t("TableName");
        QCOMPARE(QString("TableName"), t.name());
        QCOMPARE(QString(""), t.creationSql());
        QCOMPARE(QString(""), t.lastError());
        QCOMPARE(0, t.columns().size());
    }
    {
        Model::Table t("TableName", "CreationSql");
        QCOMPARE(QString("TableName"), t.name());
        QCOMPARE(QString("CreationSql"), t.creationSql());
        QCOMPARE(QString(""), t.lastError());
        QCOMPARE(0, t.columns().size());
    }
    {
        class QSqlDatabase *d;
        Model::Table t(d);
        QCOMPARE(QString(""), t.name());
        QCOMPARE(QString(""), t.creationSql());
        QCOMPARE(QString(""), t.lastError());
        QCOMPARE(0, t.columns().size());
    }
}

void TableTest::testNonWorkingIntrospect()
{
    Model::Table t("TableName", "CreationSql");
    QCOMPARE(QString("TableName"), t.name());
    QCOMPARE(QString("CreationSql"), t.creationSql());
    QCOMPARE(QString(""), t.lastError());
    QCOMPARE(0, t.columns().size());
    QCOMPARE(false, t.introspect());

    //Verify that a failed introspect does not modify other
    //properties.
    QCOMPARE(0, t.columns().size());
    QVERIFY(t.lastError() != "");
    QCOMPARE(QString("TableName"), t.name());
    QCOMPARE(QString("CreationSql"), t.creationSql());
}
