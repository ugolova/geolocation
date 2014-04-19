#include "sample2_test.h"

Sample2Test::Sample2Test(QObject *parent) :
    QObject(parent)
{
}

void Sample2Test::testCase1()
{
    QCOMPARE("b", "b");
}
