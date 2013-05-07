#include "LibModelTestSuite.h"
#include "FieldTest.h"

namespace LibModelTestSuite
{

QList<QObject*> cases()
{
    QList<QObject*> tests;
    tests << new FieldTest;
    return tests;
}

}
