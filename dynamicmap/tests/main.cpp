#include <QtTest>
#include <QApplication>
#include <iostream>

#include "sample_test.h"
#include "sample2_test.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    int result = 0;

    result |= QTest::qExec(new SampleTest(), argc, argv);

    std::cout << std::endl;

    result |= QTest::qExec(new Sample2Test(), argc, argv);

    return result;
}
