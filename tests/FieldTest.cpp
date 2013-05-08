#include "FieldTest.h"
#include <QtTest/QtTest>
#include <QString>

#include <model/Field.h>

void FieldTest::testToCreateDefinition_data()
{
    QTest::addColumn<QString>("result");
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("type");
    QTest::addColumn<bool>("notnull");
    QTest::addColumn<bool>("pk");
    QTest::addColumn<QString>("dflt");
    QTest::addColumn<int>("id");

    QTest::newRow("1") << "id INTEGER PRIMARY KEY NOT NULL" << "id" << "INTEGER" << true << true << "" << -1;
    QTest::newRow("2") << "value float" << "value" << "float" << false << false << "  " << -1;
    QTest::newRow("3") << "value float DEFAULT 3.1415" << "value" << "float" << false << false << "3.1415" << -1;
    QTest::newRow("3") << "name varchar(255) NOT NULL" << "name" << "varchar(255)" << true << false << "" << -1;
    QTest::newRow("3") << "name varchar(255)" << "name" << "varchar(255)" << false << false << "" << -1;
    QTest::newRow("3") << "name varchar(255) PRIMARY KEY" << "name" << "varchar(255)" << false << true << "" << -1;
}

void FieldTest::testToCreateDefinition()
{

    QFETCH(QString,result);
    QFETCH(QString,dflt);
    QFETCH(QString,name);
    QFETCH(QString,type);
    QFETCH(bool,notnull);
    QFETCH(bool,pk);
    QFETCH(int,id);

    Model::Field f;
    f.setName(name);
    f.setType(type);
    f.setPrimaryKey(pk);
    f.setNotNullFlag(notnull);
    f.setId(id);
    f.setDfltValue(dflt);

    QCOMPARE(result, f.toCreateDefinition());
}

void FieldTest::testAssignmentOperator()
{
    Model::Field f1;
    Model::Field f2;

    f1.setName("A name");
    QVERIFY(f1 != f2);
    f2 = f1;
    QVERIFY(f1 == f2);

}


void FieldTest::testCopyConstructor()
{
    Model::Field f1;
    Model::Field f2;

    f1.setName("A name");
    QVERIFY(f1 != f2);
    Model::Field f3(f1);
    QVERIFY(f1 == f3);

}

void FieldTest::testDefaultConstructor()
{
    Model::Field f;
    QCOMPARE(QString(""), f.name());
    QCOMPARE(QString(""), f.type());
    QCOMPARE(QString(""), f.dfltValue());
    QCOMPARE(-1, f.id());
    QCOMPARE(false, f.isPrimaryKey());
    QCOMPARE(false, f.isNotNullFlagSet());
}


void FieldTest::testSettersAndGetters()
{
    Model::Field f;

    QCOMPARE(QString(""), f.name());
    QCOMPARE(QString(""), f.dfltValue());
    QCOMPARE(QString(""), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(false, f.isNotNullFlagSet());
    QCOMPARE(false, f.isPrimaryKey());

    f.setName("A name");
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString(""), f.dfltValue());
    QCOMPARE(QString(""), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(false, f.isNotNullFlagSet());
    QCOMPARE(false, f.isPrimaryKey());

    f.setType("A type");
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString(""), f.dfltValue());
    QCOMPARE(QString("A type"), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(false, f.isNotNullFlagSet());
    QCOMPARE(false, f.isPrimaryKey());

    f.setDfltValue("Default value");
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString("Default value"), f.dfltValue());
    QCOMPARE(QString("A type"), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(false, f.isNotNullFlagSet());
    QCOMPARE(false, f.isPrimaryKey());

    f.setNotNullFlag(true);
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString("Default value"), f.dfltValue());
    QCOMPARE(QString("A type"), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(true, f.isNotNullFlagSet());
    QCOMPARE(false, f.isPrimaryKey());

    f.setPrimaryKey(true);
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString("Default value"), f.dfltValue());
    QCOMPARE(QString("A type"), f.type());
    QCOMPARE(-1, f.id());
    QCOMPARE(true, f.isNotNullFlagSet());
    QCOMPARE(true, f.isPrimaryKey());

    f.setId(42);
    QCOMPARE(QString("A name"), f.name());
    QCOMPARE(QString("Default value"), f.dfltValue());
    QCOMPARE(QString("A type"), f.type());
    QCOMPARE(42, f.id());
    QCOMPARE(true, f.isNotNullFlagSet());
    QCOMPARE(true, f.isPrimaryKey());

}

void FieldTest::testEqualsOperator()
{
    Model::Field f1;
    Model::Field f2;
    QVERIFY(f1 == f2);

    f1.setId(45);
    f2.setId(66);
    QVERIFY(f1 == f2);

    f1.setName("N");
    QVERIFY(f1 != f2);
    f2.setName("N");
    QVERIFY(f1 == f2);

    f1.setType("T");
    QVERIFY(f1 != f2);
    f2.setType("T");
    QVERIFY(f1 == f2);

    f1.setDfltValue("D");
    QVERIFY(f1 != f2);
    f2.setDfltValue("D");
    QVERIFY(f1 == f2);

    f1.setNotNullFlag(true);
    f2.setNotNullFlag(false);
    QVERIFY(f1 != f2);
    f2.setNotNullFlag(true);
    QVERIFY(f1 == f2);

    f1.setPrimaryKey(true);
    f2.setPrimaryKey(false);
    QVERIFY(f1 != f2);
    f2.setPrimaryKey(true);
    QVERIFY(f1 == f2);
}

