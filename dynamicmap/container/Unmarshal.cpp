#include "Unmarshal.h"


using namespace dynamicMap;


MultiGraph<double, Station>* Unmarshal::readObject(std::string fileName)
{
	std::ifstream in(fileName);

	MultiGraph<double, Station>* graph = new MultiGraph<double, Station>();

	if (in.is_open())
	{
		std::string str;
		while (std::getline(in,str))
		{
			std::string temp;
			std::stringstream ss(str);
			char delim = '-';
			
			Station *startStation = 0;
			Station *endStation = 0;
			double *lenght = 0;
			int i = 0;
			while (std::getline(ss, temp, delim))
			{
				
				if (i == 0 || i == 1){
					std::stringstream ssName(temp);
					std::string name;
					

					char leftDelim = '[';
					char seperator = ':';
					std::getline(ssName, name, leftDelim);

					ssName.str(temp);
					std::string latitude ,longitude;
					std::getline(ssName, latitude, seperator);
					int len = temp.length() - latitude.length() - 2;
					longitude = temp.substr(latitude.length() + 1 ,len);
					latitude = latitude.substr(name.length() + 1);
					std::cout << latitude << "\n";
					std::cout << longitude << "\n";
					if (i == 0)
					{
						double longS = atof(longitude.c_str());
						double laS = atof(latitude.c_str());
						startStation = new Station(name, longS, laS);
					}
					else
					{
						double longS = atof(longitude.c_str());
						double laS = atof(latitude.c_str());
						endStation = new Station(name, longS, laS);
					}
				}				
				else if (i == 2)
				{
					temp = temp.substr(1, temp.length() - 2);
					lenght = new double(atof(temp.c_str()));
					std::cout << *lenght << "\n";
				}
				i++;
				//TODO
			}

			graph->addPathToVertex(startStation, endStation, lenght);
		}
	}

	in.close();
	return graph;
}

