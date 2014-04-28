#ifndef ALGORITHM_TEST_H
#define ALGORITHM_TEST_H

#include <QtTest>
#include <string>

#include "../../dynamicmap_src/container/algorithm.h"
#include "../dynamicmap_src/controller_gui.h"
#include "../../dynamicmap_src/container/multigraph.h"
#include "../../dynamicmap_src/container/serialization.h"

class AlgorithmTest : public QObject
{
    Q_OBJECT

public:
    explicit AlgorithmTest(QObject *parent = 0);

private Q_SLOTS:
    void testFindShortestPath();
};

#endif // ALGORITHM_TEST_H
