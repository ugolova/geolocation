#pragma once

#include "Station.h"
#include "MultiGraph.h"
#include <iostream>
#include <sstream>
#include <fstream>


namespace dynamicMap{
	class Unmarshal
	{
	public:
		static MultiGraph<double, Station> * readObject(std::string fileName);
	};
}

