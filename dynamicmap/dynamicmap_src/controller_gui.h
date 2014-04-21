#ifndef CONTROLLER_GUI_H
#define CONTROLLER_GUI_H

#include <QString>
#include "container/multigraph.h"
#include "container/station.h"

using namespace container;

class ControllerGUI
{
private:
    ControllerGUI();
public:
    static void addStation(MultiGraph<double, Station>* graph, QString name, int type, QString lat, QString lon);
    static void delStation(MultiGraph<double, Station>* graph, QString name);
};

#endif // CONTROLLER_GUI_H
