#include "LibModelTestSuite.h"
#include "FieldTest.h"
#include "TableTest.h"
#include "DataBaseTest.h"


namespace LibModelTestSuite
{

QList<QObject*> cases()
{
    QList<QObject*> tests;
    tests << new FieldTest;
    tests << new TableTest;
    tests << new DataBaseTest;
    return tests;
}

}
