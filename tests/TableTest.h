#ifndef TABLETEST_H
#define TABLETEST_H

#include <QObject>

class TableTest : public QObject
{
    Q_OBJECT

private slots:
    void testConstructors();
    void testNonWorkingIntrospect();
};

#endif // TABLETEST_H
