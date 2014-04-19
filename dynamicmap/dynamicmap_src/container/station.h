#ifndef STATION_H
#define STATION_H

#include <string>

class StationTest;

class Station
{
    friend class StationTest;
private:
	std::string name;
    double longitude;
    double latitude;
    bool isRailRoadStation;

public:
	Station();

	Station(std::string name, double longitude, double latitude ,bool isRailRoadStation);
	void setLongitude(double longitude);
	void setLatitude(double latitude);
	double getLongitude() const;
	double getLatitude() const;

	void setName(std::string name);
	std::string getName();
	bool operator == (const Station &obj);
	~Station();
};

#endif // STATION_H
