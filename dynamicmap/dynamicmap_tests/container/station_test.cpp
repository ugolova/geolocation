#include "station_test.h"

StationTest::StationTest(QObject *parent) :
    QObject(parent)
{
}

void StationTest::testGetName()
{
    std::string testName = "testName";
    Station st;
    st.name = testName;
    QCOMPARE(st.getName(), testName);
}

void StationTest::testSetName()
{
    std::string testName = "testName";
    Station st;
    st.setName(testName);
    QCOMPARE(st.name, testName);
}

void StationTest::testGetLatitude()
{
    double testLat = 10.1;
    Station st;
    st.latitude = testLat;
    QCOMPARE(st.getLatitude(), testLat);
}

void StationTest::testSetLatitude()
{
    double testLat = 10.1;
    Station st;
    st.setLatitude(testLat);
    QCOMPARE(st.latitude, testLat);
}

void StationTest::testGetLongitude()
{
    double testLon = 10.1;
    Station st;
    st.longitude = testLon;
    QCOMPARE(st.getLongitude(), testLon);
}

void StationTest::testSetLongitude()
{
    double testLon = 10.1;
    Station st;
    st.setLongitude(testLon);
    QCOMPARE(st.longitude, testLon);
}

void StationTest::testConstructor()
{
    /*
    std::string testName = "testName";
    double testLon = 10.1;
    double testLat = 20.2;
    bool testIsRailRoad = true;
    Station st(std::string name, double longitude, double latitude ,bool isRailRoadStation)
    */
}
