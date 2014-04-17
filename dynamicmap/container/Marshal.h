#pragma once

#include "MultiGraph.h"
#include "Station.h"
#include <iostream>
#include <fstream>


namespace dynamicMap{

	class Marshal
	{
	private:
		
	public:

		static void writeObject(MultiGraph<double, Station> *graph, std::string fileName);


		
	};
}

