#include "road.h"


Road::Road()
{
}

Road::Road(Station* start, Station* end)
{
	this->start = start;
	this->end = end; 
}
Station* Road::getStart()
{
	return start;
}
Station* Road::getEnd()
{
	return end;
}
void Road::setStart(Station* start)
{
	this->start = start;
}
void Road::setEnd(Station* end)
{
	this->end = end;
}
double Road::getLenght()
{
	return lenght;
}
void Road::setLenght(double lenght)
{
	this->lenght = lenght;
}

Road::~Road()
{
}
