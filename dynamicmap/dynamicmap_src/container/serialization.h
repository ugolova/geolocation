#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "station.h"
#include "multigraph.h"
#include "../exceptions/cannot_open_file_exception.h"
#include "../exceptions/incorrect_file_format_exception.h"

using namespace container;

class Serialization
{
private:
    Serialization();
    ~Serialization();
public:
    static MultiGraph<double, Station> * readObject(QString fileName) throw(DynamicMapException);
    static void writeObject(MultiGraph<double, Station> *graph, QString fileName) throw(CannotOpenFileException);
};

#endif // SERIALIZATION_H
