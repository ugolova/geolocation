#pragma once
#include<string>

class Station
{
private:
	std::string name;

public:
	Station();

	Station(std::string name);

	void setName(std::string name);
	std::string getName();
	bool operator == (Station* obj);
	~Station();
};

