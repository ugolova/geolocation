#include "station.h"


Station::Station():
    longitude(0),
    latitude(0),
    isRailRoadStation(true)
{
}

Station::Station(std::string name, double longitude, double latitude, bool isRailRoadStation)
{
	this->name = name; 
	this->longitude = longitude;
	this->latitude = latitude;
	this->isRailRoadStation = isRailRoadStation;
}

void Station::setName(std::string name)
{
	this->name = name;
}

std::string Station::getName()
{
	return name;
}
void Station::setLongitude(double longitude)
{
	this->longitude = longitude;

}
void Station::setLatitude(double latitude)
{
	this->latitude = latitude;
}

double Station::getLongitude() const
{
	return longitude;
}
double Station::getLatitude() const
{
	return latitude;
}

bool Station :: operator == (const Station &obj)
{
	int i = name.compare(obj.name);
	if (i == 0 && obj.latitude == latitude && obj.longitude == longitude)
		return 1;
	return 0;
}


Station::~Station()
{
		
}
