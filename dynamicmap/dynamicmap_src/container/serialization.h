#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "station.h"
#include "multigraph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace container;

class Serialization
{
public:
    Serialization();
    static MultiGraph<double, Station> * readObject(const char* fileName);
    static void writeObject(MultiGraph<double, Station> *graph, const char* fileName);
};

#endif // SERIALIZATION_H
