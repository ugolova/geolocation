#include "Marshal.h"

using namespace dynamicMap;


void Marshal::writeObject(MultiGraph<double, Station> *graph ,std::string fileName)
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


