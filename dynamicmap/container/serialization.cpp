#include "serialization.h"

Serialization::Serialization()
{
}

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
                    std::cout << start->getName() << "[" << start->getLatitude() << ":" << start->getLongitude() << "]" << "-"
                        << end->getName() << "[" << end->getLatitude() << ":" << end->getLongitude() << "]" << "-[" << *lenghts->get(k) << "]" << std::endl;
                    out << start->getName() << "[" << start->getLatitude() << ":" << start->getLongitude() << "]" << "-"
                        << end->getName() << "[" << end->getLatitude() << ":" << end->getLongitude() << "]" << "-[" << *lenghts->get(k) << "]" << std::endl;
                }
            }
        }
    }
    out.close();
}
