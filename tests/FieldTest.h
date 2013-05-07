#ifndef FIELDTEST_H
#define FIELDTEST_H

#include <QObject>

class FieldTest : public QObject
{
    Q_OBJECT
    
private slots:
    void testToCreateDefinition();
    void testToCreateDefinition_data();

};



#endif // FIELDTEST_H
