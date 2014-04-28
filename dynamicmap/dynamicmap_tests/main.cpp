#include <QApplication>
#include <iostream>

#include "authentication_test.h"
#include "container/station_test.h"
#include "container/road_test.h"
#include "sample_test.h"
#include "container/algorithm_test.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    int result = 0;

    result |= QTest::qExec(new AuthenticationTest(), argc, argv);

    std::cout << std::endl;

    result |= QTest::qExec(new StationTest(), argc, argv);

    std::cout << std::endl;

    result |= QTest::qExec(new SampleTest(), argc, argv);

    std::cout << std::endl;

    result |= QTest::qExec(new RoadTest(), argc, argv);

    std::cout << std::endl;

    result |= QTest::qExec(new AlgorithmTest(), argc, argv);

    return result;
}
