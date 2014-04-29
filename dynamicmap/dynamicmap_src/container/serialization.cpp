#include "serialization.h"

QString Serialization::pStation = "[^\\[]+"; // "[\\dA-Za-zА-Яа-яЁё]{1}[\\dA-Za-zА-Яа-яЁё\\-\\(\\) ]*";

QString Serialization::pDouble = "[\\d]+|[\\d]+\\.[\\d]+"; // integer or double

QString Serialization::pType = "[012]{1}";

QString Serialization::getStationPattern()
{
    return pStation;
}

MultiGraph<double, Station>* Serialization::readObject(QString fileName) throw(DynamicMapException)
{
    QFile file(fileName);
    bool opened = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!opened) {
        throw CannotOpenFileException(fileName);
    }
    QTextStream in(&file);

    QString pStationData = "(" + pStation + ")\\[(" + pDouble + "):(" + pDouble + ")\\]/(" + pType + ")";
    QRegExp regexp("^" + pStationData + "-" + pStationData + "-\\[(" + pDouble + ")\\]" + "$");

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

        double *distance = new double(QString::number(regexp.cap(9).toDouble()).toDouble()); // precision workaround

        if (*distance <= 0) {
            throw IncorrectFileFormatException(QString::number(lineCounter));
        }

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
