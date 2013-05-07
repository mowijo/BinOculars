#include <QApplication>
#include <QDebug>
#include <QtTest/QtTest>

#include "LibModelTestSuite.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QList<QObject*> tests;

    tests << LibModelTestSuite::cases();

    foreach(QObject *test, tests)
    {
        if( QTest::qExec(test) > 0)
        {
            qDebug() << "\n\nFAILURE !!!\n\n";
            return 1;
        }
    }
    qDebug() << "\n\nSUCCESS!!!\n\n";
    return 0;
}
