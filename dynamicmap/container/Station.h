#pragma once
#include<string>


class Station
{
private:
	std::string name;
	double longitude = 0;
	double latitude = 0;


public:
	Station();

	Station(std::string name, double longitude, double latitude);
	void setLongitude(double longitude);
	void setLatitude(double latitude);
	double getLongitude() const;
	double getLatitude() const;

	void setName(std::string name);
	std::string getName();
	bool operator == (const Station &obj);
	~Station();
};

