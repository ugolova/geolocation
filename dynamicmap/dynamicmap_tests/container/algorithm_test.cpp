#include "algorithm_test.h"

AlgorithmTest::AlgorithmTest(QObject *parent) :
    QObject(parent)
{
}

void AlgorithmTest::testFindShortestPath()
{
    /*
    QString fileName="../algorithmTest.txt";
    MultiGraph<double, Station> *container = Serialization::readObject(fileName);
    QString stationA="A";
    QString stationC="C";
    Station *stA = ControllerGUI::getStationByName(container, stationA);
    Station *stC = ControllerGUI::getStationByName(container, stationC);
    double length = 0;
    Algorithm::findShortestPath(container, stA, stC, length);
    QCOMPARE(3.0, length); //double, поэтому 3.0 (ненужный коммент:))
    */
}
