#include "Point.h"

using namespace dynamicMap;

Point::Point() :longitude(0), latitude(0)
{

}


Point::Point(double longitude, double latitude)
{
	this->longitude = longitude;
	this->latitude = latitude;

}


void Point::setLongitude(double longitude)
{
	this->longitude = longitude;

}
void Point::setLatitude(double latitude)
{
	this->latitude = latitude;
}

double Point::getLongitude() const
{
	return longitude;
}
double Point::getLatitude() const
{
	return latitude;
}

bool Point ::operator == (const Point &obj)
{
	return latitude == obj.latitude
		&& longitude == obj.longitude;
}

Point::~Point()
{
}