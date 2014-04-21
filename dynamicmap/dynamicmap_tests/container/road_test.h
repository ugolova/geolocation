#ifndef ROAD_TEST_H
#define ROAD_TEST_H

#include <QtTest>
#include <string>

#include "../../dynamicmap_src/container/road.h"

class RoadTest : public QObject
{
    Q_OBJECT

public:
    explicit RoadTest(QObject *parent = 0);

private Q_SLOTS:
    void testGetStart();
    void testSetStart();
    void testGetEnd();
    void testSetEnd();
    void testGetLenght();
    void testSetLenght();
    void testConstructor();
};

#endif // ROAD_TEST_H
