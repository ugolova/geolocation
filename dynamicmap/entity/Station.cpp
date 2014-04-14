#include "Station.h"


Station::Station()
{
}

Station::Station(std::string name)
{
	this->name = name; 
}

void Station::setName(std::string name)
{
	this->name = name;
}

std::string Station::getName()
{
	return name;
}
bool Station :: operator == (Station* obj)
{
	int i = name.compare(obj->getName());
	if (i == 0)
		return 1;
	return 0;
}


Station::~Station()
{
}
