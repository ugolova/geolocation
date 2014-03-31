#pragma once
#include"Point.h"
#include<vector>


namespace dynamicMap{

	class Road
	{
	private:
		std::string startStation;
		std::string endStation;
		double lenght;
		std::vector<Point> points;


	public:
		Road();
		Road(std::string startStation, std::string endStation);

		void setStartStation(std::string startStation);
		void setEndStation(std::string endStation);
		std::string getStartStation() const;
		std::string getEndStation() const;
		double getLenght() const;
		void setLenght(double lenght);

		void addPoint(const Point& point);
		bool removePoint(const Point& point);
		
		~Road();
	};
}

