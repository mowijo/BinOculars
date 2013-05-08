#include "DataBaseTest.h"
#include <QtTest/QtTest>
#include <model/DataBase.h>
#include <model/Table.h>
#include <model/Field.h>
#include <QDebug>


void DataBaseTest::testLoadingSmallDatabase()
{
    QString dbname = createTestDataBaseOnDiskFromString("database-1");
    {
        Model::DataBase database;
        QVERIFY(database.open(dbname));
        QCOMPARE(QString(""), database.lastError());
        QCOMPARE(database.tables().size(), 1);
        Model::Table *table = database.tables()[0];
        QCOMPARE(table->columns().size(), 2);

        QCOMPARE(table->name(), QString("AAA"));

        Model::Field *f = table->columns()[0];
        QCOMPARE(f->name(), QString("id"));
        QCOMPARE(f->type(), QString("integer"));
        QCOMPARE(f->isPrimaryKey(), true);
        QCOMPARE(f->isNotNullFlagSet(), true);
        QCOMPARE(f->dfltValue(), QString(""));

        f = table->columns()[1];
        QCOMPARE(f->name(), QString("name"));
        QCOMPARE(f->type(), QString("text"));
        QCOMPARE(f->isPrimaryKey(), false);
        QCOMPARE(f->isNotNullFlagSet(), false);
        QCOMPARE(f->dfltValue(), QString(""));

        QSqlQuery query = database.exec("select * from AAA");
        query.next();
        QVERIFY(query.isValid());
        QCOMPARE(query.value(0).toInt(), 1);
        QCOMPARE(query.value(1).toString(), QString("Row 1"));

        query.next();
        QVERIFY(query.isValid());
        QCOMPARE(query.value(0).toInt(), 2);
        QCOMPARE(query.value(1).toString(), QString("Row 2"));

        query.next();
        QVERIFY(query.isValid());
        QCOMPARE(query.value(0).toInt(), 3);
        QCOMPARE(query.value(1).toString(), QString("Row 3"));

        query.next();
        QVERIFY(query.isValid());
        QCOMPARE(query.value(0).toInt(), 4);
        QCOMPARE(query.value(1).toString(), QString("Row 4"));

        query.next();
        QVERIFY(!query.isValid());
    }
}

void DataBaseTest::testAddingAndDroppingTable()
{
    QString dbname = createTestDataBaseOnDiskFromString("database-1");
    Model::DataBase database;
    QVERIFY(database.open(dbname));
    QCOMPARE(QString(""), database.lastError());
    QCOMPARE(database.tables().size(), 1);

    database.exec("create table BBB (name text, position text)");
    QCOMPARE(database.tables().size(), 2);

    Model::Table *table;
    foreach(Model::Table *candidate, database.tables())
    {
        if(candidate->name() == "BBB")
        {
            table = candidate;
            break;
        }
    }
    QCOMPARE(table->columns().size(), 2);
    QCOMPARE(table->name(), QString("BBB"));


    Model::Field *f = table->columns()[0];
    QCOMPARE(f->name(), QString("name"));
    QCOMPARE(f->type(), QString("text"));
    QCOMPARE(f->isPrimaryKey(), false);
    QCOMPARE(f->isNotNullFlagSet(), false);
    QCOMPARE(f->dfltValue(), QString(""));

    f = table->columns()[1];
    QCOMPARE(f->name(), QString("position"));
    QCOMPARE(f->type(), QString("text"));
    QCOMPARE(f->isPrimaryKey(), false);
    QCOMPARE(f->isNotNullFlagSet(), false);
    QCOMPARE(f->dfltValue(), QString(""));

    database.exec("drop table BBB ");
    QCOMPARE(database.tables().size(), 1);

    table = database.tables()[0];
    QCOMPARE(table->columns().size(), 2);

    QCOMPARE(table->name(), QString("AAA"));

    f = table->columns()[0];
    QCOMPARE(f->name(), QString("id"));
    QCOMPARE(f->type(), QString("integer"));
    QCOMPARE(f->isPrimaryKey(), true);
    QCOMPARE(f->isNotNullFlagSet(), true);
    QCOMPARE(f->dfltValue(), QString(""));

    f = table->columns()[1];
    QCOMPARE(f->name(), QString("name"));
    QCOMPARE(f->type(), QString("text"));
    QCOMPARE(f->isPrimaryKey(), false);
    QCOMPARE(f->isNotNullFlagSet(), false);
    QCOMPARE(f->dfltValue(), QString(""));
}
