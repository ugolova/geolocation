#ifndef ROAD_H
#define ROAD_H

#include"station.h"

class Road
{
private:
	Station* start;
	Station* end;
	double lenght;
public:

	Road();
	Road(Station* start, Station* end, double lenght);
	Station* getStart();
	Station* getEnd();
	void setStart(Station* start);
	void setEnd(Station* end);
	double getLenght();
	void setLenght(double lenght);

	~Road();
};

#endif 
