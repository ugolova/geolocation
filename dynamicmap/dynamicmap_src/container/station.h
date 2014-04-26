#ifndef STATION_H
#define STATION_H

#include <QString>

class StationTest;

class Station
{
    friend class StationTest;
private:
    QString name;
    double longitude;
    double latitude;
    int type;

public:
	Station();

    Station(QString name, double longitude, double latitude ,int type);
	void setLongitude(double longitude);
	void setLatitude(double latitude);
	double getLongitude() const;
	double getLatitude() const;
	int getType();


    void setName(QString name);
    QString getName();
	bool operator == (const Station &obj);
	~Station();
};

#endif // STATION_H
