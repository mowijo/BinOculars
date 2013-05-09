#include "TableTest.h"
#include <model/Table.h>
#include <model/Field.h>
#include <model/DataBase.h>
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
        d = 0;
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



void TableTest::testAddInvalidField()
{
    Model::Table t("TableName");
    Model::Field f;
    f.setName("");
    f.setType("text");
    QVERIFY( ! t.addField(f, 1));

    f.setName("name");
    f.setType("");
    QVERIFY( ! t.addField(f, 1));

    f.setName("name");
    f.setType("number");
    f.setPrimaryKey(true);
    QVERIFY( ! t.addField(f, 1));

    f.setName("name");
    f.setType("number");
    f.setNotNullFlag(true);
    f.setPrimaryKey(false);
    f.setDfltValue("");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("null \n");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("  \n\tNULL ");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("CURRENT_DATE");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("CURRENT_TIME");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("CURRENT_TIMESTAMP");
    QVERIFY( ! t.addField(f, 1));
    f.setDfltValue("  ( sfas dfasdf ) \n\t ");
    QVERIFY( ! t.addField(f, 1));
}

void TableTest::testAddFieldInTheMiddle()
{
    QString dbname = createTestDataBaseOnDiskFromString("database-1");
    {
        Model::DataBase database;
        QVERIFY(database.open(dbname));
        QCOMPARE(QString(""), database.lastError());

        QCOMPARE(database.tables().size(), 1);
        Model::Table *t = database.tables()[0];

        QCOMPARE(t->columns().size(), 2);
        Model::Field *candidate = t->columns()[0];
        QCOMPARE(candidate->name(), QString("id"));
        QCOMPARE(candidate->type(), QString("integer"));

        candidate = t->columns()[1];
        QCOMPARE(candidate->name(), QString("name"));
        QCOMPARE(candidate->type(), QString("text"));

        Model::Field newfield;
        newfield.setName("NewColumn");
        newfield.setType("text");
        newfield.setDfltValue("\"I am new\"");

        QSqlQuery q = database.exec("select * from AAA");

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 1);
        QCOMPARE(q.value(1).toString(), QString("Row 1"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 2);
        QCOMPARE(q.value(1).toString(), QString("Row 2"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 3);
        QCOMPARE(q.value(1).toString(), QString("Row 3"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 4);
        QCOMPARE(q.value(1).toString(), QString("Row 4"));

        q.next();
        QVERIFY(!q.isValid());

        if(!t->addField(newfield, 1))
        {
            qDebug() << "ERROR" << t->lastError();
        }
    }

    {
        Model::DataBase database;
        QVERIFY(database.open(dbname));
        QCOMPARE(QString(""), database.lastError());

        QCOMPARE(database.tables().size(), 1);
        Model::Table *t = database.tables()[0];

        QCOMPARE(t->columns().size(), 3);
        Model::Field *candidate = t->columns()[0];
        QCOMPARE(candidate->name(), QString("id"));
        QCOMPARE(candidate->type(), QString("integer"));

        candidate = t->columns()[1];
        QCOMPARE(candidate->name(), QString("NewColumn"));
        QCOMPARE(candidate->type(), QString("text"));

        candidate = t->columns()[2];
        QCOMPARE(candidate->name(), QString("name"));
        QCOMPARE(candidate->type(), QString("text"));

        QSqlQuery q = database.exec("select * from AAA");

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 1);
        QCOMPARE(q.value(1).toString(), QString("I am new"));
        QCOMPARE(q.value(2).toString(), QString("Row 1"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 2);
        QCOMPARE(q.value(1).toString(), QString("I am new"));
        QCOMPARE(q.value(2).toString(), QString("Row 2"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 3);
        QCOMPARE(q.value(1).toString(), QString("I am new"));
        QCOMPARE(q.value(2).toString(), QString("Row 3"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 4);
        QCOMPARE(q.value(1).toString(), QString("I am new"));
        QCOMPARE(q.value(2).toString(), QString("Row 4"));

        q.next();
        QVERIFY( ! q.isValid());


    }
}


void TableTest::testAddFieldAtTheEnd()
{
    QString dbname = createTestDataBaseOnDiskFromString("database-1");
    {
        Model::DataBase database;
        QVERIFY(database.open(dbname));
        QCOMPARE(QString(""), database.lastError());

        QCOMPARE(database.tables().size(), 1);
        Model::Table *t = database.tables()[0];

        QCOMPARE(t->columns().size(), 2);
        Model::Field *candidate = t->columns()[0];
        QCOMPARE(candidate->name(), QString("id"));
        QCOMPARE(candidate->type(), QString("integer"));

        candidate = t->columns()[1];
        QCOMPARE(candidate->name(), QString("name"));
        QCOMPARE(candidate->type(), QString("text"));

        Model::Field newfield;
        newfield.setName("NewColumn");
        newfield.setType("text");
        newfield.setDfltValue("\"I am new\"");

        QSqlQuery q = database.exec("select * from AAA");

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 1);
        QCOMPARE(q.value(1).toString(), QString("Row 1"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 2);
        QCOMPARE(q.value(1).toString(), QString("Row 2"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 3);
        QCOMPARE(q.value(1).toString(), QString("Row 3"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 4);
        QCOMPARE(q.value(1).toString(), QString("Row 4"));

        q.next();
        QVERIFY(!q.isValid());

        if(!t->addField(newfield))
        {
            qDebug() << "ERROR" << t->lastError();
        }
    }

    {
        Model::DataBase database;
        QVERIFY(database.open(dbname));
        QCOMPARE(QString(""), database.lastError());

        QCOMPARE(database.tables().size(), 1);
        Model::Table *t = database.tables()[0];

        QCOMPARE(t->columns().size(), 3);
        Model::Field *candidate = t->columns()[0];
        QCOMPARE(candidate->name(), QString("id"));
        QCOMPARE(candidate->type(), QString("integer"));

        candidate = t->columns()[1];
        QCOMPARE(candidate->name(), QString("name"));
        QCOMPARE(candidate->type(), QString("text"));

        candidate = t->columns()[2];
        QCOMPARE(candidate->name(), QString("NewColumn"));
        QCOMPARE(candidate->type(), QString("text"));


        QSqlQuery q = database.exec("select * from AAA");

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 1);
        QCOMPARE(q.value(1).toString(), QString("Row 1"));
        QCOMPARE(q.value(2).toString(), QString("I am new"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 2);
        QCOMPARE(q.value(1).toString(), QString("Row 2"));
        QCOMPARE(q.value(2).toString(), QString("I am new"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 3);
        QCOMPARE(q.value(1).toString(), QString("Row 3"));
        QCOMPARE(q.value(2).toString(), QString("I am new"));

        q.next();
        QVERIFY(q.isValid());
        QCOMPARE(q.value(0).toInt(), 4);
        QCOMPARE(q.value(1).toString(), QString("Row 4"));
        QCOMPARE(q.value(2).toString(), QString("I am new"));

        q.next();
        QVERIFY( ! q.isValid());


    }
}
