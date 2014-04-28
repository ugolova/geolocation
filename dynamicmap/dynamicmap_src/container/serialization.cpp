#include "serialization.h"

MultiGraph<double, Station>* Serialization::readObject(QString fileName) throw(DynamicMapException)
{
    QFile file(fileName);
    bool opened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!opened) {
        throw CannotOpenFileException(fileName);
    }
    QTextStream in(&file);

    // regexp patterns
    QString pDouble = "[\\d]+\\.[\\d]+"; // TODO: allow integers
    QString pStation = "[^\\[]+"; // TODO: make good regexp
    QString pLon = pDouble;
    QString pLat = pDouble;
    QString pType = "[\\d]{1}";
    QString pDistance = pDouble;
    QString pStationData = "(" + pStation + ")\\[(" + pLon + "):(" + pLat + ")\\]/(" + pType + ")";

    // result regexp
    QRegExp regexp("^" + pStationData + "-" + pStationData + "-\\[(" + pDistance + ")\\]" + "$");

    MultiGraph<double, Station>* graph = new MultiGraph<double, Station>();

    int lineCounter = 1;
    QString str = NULL;
    while ((str = in.readLine()) != NULL)
    {
        int pos = regexp.indexIn(str);

        if (pos == -1) {
            throw IncorrectFileFormatException(QString::number(lineCounter));
        }

        QString startStationName = regexp.cap(1).trimmed();
        double startStationLon = regexp.cap(2).toDouble();
        double startStationLat = regexp.cap(3).toDouble();
        int startStationType = regexp.cap(4).toInt();

        QString endStationName = regexp.cap(5).trimmed();
        double endStationLon = regexp.cap(6).toDouble();
        double endStationLat = regexp.cap(7).toDouble();
        int endStationType = regexp.cap(8).toInt();

        double *distance = new double(regexp.cap(9).toDouble());

        Station *startStation = new Station(startStationName, startStationLon, startStationLat, startStationType);
        Station *endStation = new Station(endStationName, endStationLon, endStationLat, endStationType);

        graph->addPathToVertex(startStation, endStation, distance);
        graph->addPathToVertex(endStation, startStation, distance);

        lineCounter++;
    }

    file.close();
    return graph;
}

void Serialization::writeObject(MultiGraph<double, Station> *graph, QString fileName) throw(CannotOpenFileException)
{
    QFile file(fileName);
    bool opened = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!opened) {
        throw CannotOpenFileException(fileName);
    }
    QTextStream out(&file);

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
                    out << start->getName() << "[" << start->getLongitude() << ":" << start->getLatitude() << "]/" << start->getType() << "-"
                        << end->getName() << "[" << end->getLongitude() << ":" << end->getLatitude() << "]/" <<end->getType() << "-[" << *lenghts->get(k) << "]" << endl;
                }
            }
        }
    }
    file.close();
}
