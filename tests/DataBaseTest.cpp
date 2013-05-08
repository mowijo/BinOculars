#include "DataBaseTest.h"
#include <QDir>
#include <QtTest/QtTest>
#include <model/DataBase.h>
#include <model/Table.h>
#include <model/Field.h>
#include <QDebug>

QString DataBaseTest::createTestDataBaseOnDiskFromString(const QString &filename)
{
    static int i = 1;
    QString outfilename = QDir::tempPath()+"/BinOkularsDataBaseTest-number-"+QString::number(i++);
    temporaryfiles << outfilename;
    QFile out(outfilename);
    out.open(QFile::WriteOnly);

    QFile in(":/TestResources/Model/"+filename);
    in.open(QFile::ReadOnly);
    out.write(in.readAll());
    out.close();
    in.close();
    return outfilename;
}

void DataBaseTest::tearDown()
{
    foreach(QString filename, temporaryfiles)
    {
        QFile::remove(filename);
    }
}


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


