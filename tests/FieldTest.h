#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <QObject>

class FieldTest : public QObject
{
    Q_OBJECT
    
private slots:

    void testSettersAndGetters();
    void testEqualsOperator();

    void testAssignmentOperator();

    void testToCreateDefinition_data();
    void testToCreateDefinition();
    void testCopyConstructor();
    void testDefaultConstructor();

};



#endif // FIELDTEST_H
