#include "Road.h"


using namespace dynamicMap;

Road::Road() :startStation(NULL), endStation(NULL), lenght(0)
{

}

Road::Road(std::string startStation, std::string endStation) :lenght(0)
{
	this->startStation = startStation;
	this->endStation = endStation;
}


void Road::setStartStation(std::string startStation)
{
	this->startStation = startStation;
}
void Road::setEndStation(std::string endStation)
{
	this->endStation = endStation;
}

std::string Road::getStartStation() const
{
	return startStation;
}

void Road::addPoint(Point point)
{
	points.push_back(point);
}

std::string Road::getEndStation() const
{
	return endStation;
}

double Road::getLenght() const
{
	return lenght;
}


Road::~Road()
{
}
