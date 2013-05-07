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
