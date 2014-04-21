#include "road_test.h"

RoadTest::RoadTest(QObject *parent) :
    QObject(parent)
{
}

void RoadTest::testGetStart()
{
    Station * testStart = new Station("xyz", 1.1, 2.2, true);
    Road rd;
    rd.start=testStart;
    QCOMPARE(rd.getStart(), testStart);
    delete testStart;
}

void RoadTest::testSetStart()
{
    Station * testStart = new Station("xyz", 1.1, 2.2, true);
    Road rd;
    rd.setStart(testStart);
    QCOMPARE(rd.start, testStart);
    delete testStart;
}

void RoadTest::testGetEnd()
{
    Station * testEnd = new Station("xyz", 1.1, 2.2, true);
    Road rd;
    rd.end=testEnd;
    QCOMPARE(rd.getEnd(), testEnd);
    delete testEnd;
}

void RoadTest::testSetEnd()
{
    Station * testEnd = new Station("xyz", 1.1, 2.2, true);
    Road rd;
    rd.setEnd(testEnd);
    QCOMPARE(rd.end, testEnd);
    delete testEnd;
}

void RoadTest::testGetLenght()
{
    double testLenght = 1.2;
    Road rd;
    rd.lenght=testLenght;
    QCOMPARE(rd.getLenght(), testLenght);
}

void RoadTest::testSetLenght()
{
    double testLenght = 1.2;
    Road rd;
    rd.setLenght(testLenght);
    QCOMPARE(rd.lenght, testLenght);
}

void RoadTest::testConstructor()
{
    /*
    Station * testStart = new Station("xyz", 1.1, 2.2, true);
    Station * testEnd = new Station("xyz", 3.3, 4.4, true);
    double testLenght = 1.2;
    Road rd(testStart, testEnd, testLenght);
    delete testStart;
    delete testEnd;
    */
}
