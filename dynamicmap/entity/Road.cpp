#include "Road.h"


using namespace dynamicMap;

Road::Road() :lenght(0)
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

std::vector<Point> Road::getPoints()
{
	return points;
}

std::string Road::getStartStation() const
{
	return startStation;
}

void Road::addPoint(const Point& point)
{
	//TODO - calc road lenght
	
	points.push_back(point);
}

bool Road::removePoint(const Point& point)
{
	//TODO
	return false;
}

std::string Road::getEndStation() const
{
	return endStation;
}

double Road::getLenght() const
{
	return lenght;
}

void Road::setLenght(double lenght)
{
	this->lenght = lenght;
}

bool Road:: operator == (Road* road)
{
	int key = startStation.compare(road->getStartStation()) + endStation.compare(road->getEndStation());
	if (key != 0 && lenght != road->getLenght())
		return false;

	if (points.size() != road->getPoints().size())
		return false;
	for (int i = 0; i < points.size(); i++)
	{
		if (points[i] != road->getPoints()[i])
			return false;
	}


	return true;
}

Road* Road:: operator = (Road* road)
{

	Road *result = new Road(road->getStartStation(), road->getEndStation());
	result->setLenght(road->getLenght());
	//TODO!!!
	//result->
	return result;	
}


Road::~Road()
{
}
