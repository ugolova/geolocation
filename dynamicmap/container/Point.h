#pragma once


#include <iostream>

namespace dynamicMap{

	
	class Point
	{
	private:
		double longitude;
		double latitude;
	public:
		Point();
		Point(double longitude, double latitude);

		void setLongitude(double longitude);
		void setLatitude(double latitude);

		double getLongitude() const;
		double getLatitude() const;

		~Point();

		bool operator == (const Point &obj);
		bool operator != (const Point &obj);
	};
}

