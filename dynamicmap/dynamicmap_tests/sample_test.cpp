#include "sample_test.h"

SampleTest::SampleTest(QObject *parent) :
    QObject(parent)
{
}

void SampleTest::testCase1()
{
    QCOMPARE("a", "a");
}
