#ifndef STATION_TEST_H
#define STATION_TEST_H

#include <QtTest>
#include <string>

#include "../../dynamicmap_src/container/station.h"

class StationTest : public QObject
{
    Q_OBJECT

public:
    explicit StationTest(QObject *parent = 0);

private Q_SLOTS:
    void testGetName();
    void testSetName();
    void testGetLatitude();
    void testSetLatitude();
    void testGetLongitude();
    void testSetLongitude();
    void testConstructor();
};

#endif // STATION_TEST_H
