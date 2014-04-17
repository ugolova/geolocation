#include "Unmarshal.h"


using namespace dynamicMap;


MultiGraph<double, Station>* Unmarshal::readObject(std::string fileName)
{
	std::ifstream in(fileName);

	if (in.is_open())
	{
		std::string str;
		while (std::getline(in,str))
		{
			std::string temp;
			std::stringstream ss(str);
			char delim = '-';
			while (std::getline(ss, temp, delim))
			{
				std::cout << temp << "\n";
				//TODO
			}
		}
	}

	in.close();
	return 0;
}

