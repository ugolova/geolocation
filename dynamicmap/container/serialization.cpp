#include "serialization.h"

Serialization::Serialization()
{
}

//TODO serialize and deserialize type of station

MultiGraph<double, Station>* Serialization::readObject(const char* fileName)
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
			bool isRailRoadStation;
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
                    //std::cout << latitude << "\n";
                    //std::cout << longitude << "\n";
                    if (i == 0)
                    {
                        double longS = 0;
                        double laS = 0;
                        std::stringstream convertLon(longitude.c_str());
                        convertLon >> longS;
                        std::stringstream convertLat(latitude.c_str());
                        convertLat >> laS;
                        startStation = new Station(name, longS, laS,1);
                    }
                    else
                    {
                        double longS = 0;
                        double laS = 0;
                        std::stringstream convertLon(longitude.c_str());
                        convertLon >> longS;
                        std::stringstream convertLat(latitude.c_str());
                        convertLat >> laS;
                        endStation = new Station(name, longS, laS,1);
                    }
                }
                else if (i == 2)
                {
                    temp = temp.substr(1, temp.length() - 2);
                    double tmpLen = 0;
                    std::stringstream convertLength(temp.c_str());
                    convertLength >> tmpLen;
                    lenght = new double(tmpLen);
                    //std::cout << *lenght << "\n";
                }
				else if (i == 3)
				{
					
				}
                i++;
                
            }

            graph->addPathToVertex(startStation, endStation, lenght);
        }
    }

    in.close();
    return graph;
}

void Serialization::writeObject(MultiGraph<double, Station> *graph ,const char* fileName)
{
    std::ofstream out(fileName);

    DynamicArray<Station> * vertexs = graph->getVertexs();
    for (int i = 0; i < vertexs->getSize(); i++)
    {
        Station * start = vertexs->get(i);
        for (int j = 0; j < vertexs->getSize(); j++)
        {
            Station * end = vertexs->get(j);
            DynamicArray<double>* lenghts = graph->getLenghtsByStation(start, end);
            if (lenghts != 0)
            {
                for (int k = 0; k < lenghts->getSize(); k++)
                {
                    //std::cout << start->getName() << "[" << start->getLatitude() << ":" << start->getLongitude() << "]" << "-"
                    //    << end->getName() << "[" << end->getLatitude() << ":" << end->getLongitude() << "]" << "-[" << *lenghts->get(k) << "]" << std::endl;
                    out << start->getName() << "[" << start->getLatitude() << ":" << start->getLongitude() << "]" << "-"
                        << end->getName() << "[" << end->getLatitude() << ":" << end->getLongitude() << "]" << "-[" << *lenghts->get(k) << "]" << std::endl;
                }
            }
        }
    }
    out.close();
}
