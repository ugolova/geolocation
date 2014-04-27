#include "mapcreator.h"

MapCreator::MapCreator(QString mapFilePostfix):
    mapApiUrl("http://api-maps.yandex.ru/2.0-stable/?load=package.full&lang=ru-RU"),
    jsMapVar("myMap"),
    mapCenterLat(59.938531),
    mapCenterLon(30.313497),
    container(NULL)
{
    mapFilePath = QDir::toNativeSeparators(QDir::tempPath()) + QDir::separator() + "dynamicmap_" + mapFilePostfix + ".html";
    htmlTitle = "dynamic_map_" + mapFilePostfix.toStdString();
}

QString MapCreator::getMapFilePath()
{
    return mapFilePath;
}

MultiGraph<double, Station>* MapCreator::getContainer()
{
    return container;
}

void MapCreator::setContainer(MultiGraph<double, Station> *container)
{
    this->container = container;
}

void MapCreator::setTableSearch(QTableWidget *table)
{
    tableSearch = table;
}

void MapCreator::makeDefaultHTML(bool withLinks)
{
    ofstream out;
    out.open(mapFilePath.toStdString().c_str());
    htmlHeader(out);

    if (container != NULL) {
        DynamicArray<Station> *arr = container->getVertexs();
        int arrSize = arr->getSize();
        for (int i = 0; i < arrSize; i++) {
            Station *st = arr->get(i);
            out << "p" << i << " = new ymaps.Placemark([" << st->getLatitude() << ", " << st->getLongitude() << "], {" << endl;
            out << "    hintContent: '" << st->getName().toStdString() << "'," << endl;
            out << "    balloonContent: '" << st->getName().toStdString() << "'," << endl;
            out << "}, {" << endl;
            out << "    preset: '" << getStationColor(st->getType()) << "'" << endl;
            out << "});" << endl;
            out << jsMapVar << ".geoObjects.add(p" << i << ");" << endl;

            if (withLinks) {
                for (int j = 0; j < arrSize; j++) {
                    if (i != j) {
                        Station *st2 = arr->get(j);
                        DynamicArray<double> *roads = container->getLenghtsByStation(st, st2);
                        if (roads != 0 && roads->getSize() > 0) {
                            out << "l" << i << j << " = new ymaps.GeoObject({" << endl;
                            out << "    geometry: {" << endl;
                            out << "        type: \"LineString\"," << endl;
                            out << "        coordinates: [" << endl;
                            out << "            [" << st->getLatitude() << ", " << st->getLongitude() << "]," << endl;
                            out << "            [" << st2->getLatitude() << ", " << st2->getLongitude() << "]" << endl;
                            out << "        ]" << endl;
                            out << "    }," << endl;
                            out << "    properties:{" << endl;
                            out << "        hintContent: \"" << st->getName().toStdString() << " - " << st2->getName().toStdString() << "\"," << endl;
                            out << "        balloonContent: \"" << st->getName().toStdString() << " - " << st2->getName().toStdString() << "\"" << endl;
                            out << "    }" << endl;
                            out << "}, {" << endl;
                            out << "    draggable: false," << endl;
                            out << "    strokeColor: \"" << getLineColor(st->getType(), st2->getType()) << "\"," << endl;
                            out << "    strokeWidth: 5" << endl;
                            out << "});" << endl;
                            out << jsMapVar << ".geoObjects.add(l" << i << j << ");" << endl;
                        }
                    }
                }
            }
        }
    }

    htmlFooter(out);
    out.close();
}

void MapCreator::makeRouteHTML(QString stationA, QString stationB) throw(UnknownStationException)
{
    Station *stA = ControllerGUI::getStationByName(container, stationA, false);
    if (stA == NULL) {
        throw UnknownStationException(stationA);
    }

    Station *stB = ControllerGUI::getStationByName(container, stationB, false);
    if (stB == NULL) {
        throw UnknownStationException(stationB);
    }

    double length = 0;
    std::vector<Road> roads = Algorithm::findShortestPath(container, stA, stB, length);

    QTableWidgetItem* header = new QTableWidgetItem("Маршрут (расстояние: " + ControllerGUI::distanceToString(length) + " км)");
    tableSearch->setHorizontalHeaderItem(0, header);

    ofstream out;
    out.open(mapFilePath.toStdString().c_str());
    htmlHeader(out);

    for(std::vector<int>::size_type i = 0; i < roads.size(); i++) {

        Road r = roads[i];
        Station *stA = r.getStart();
        Station *stB = r.getEnd();

        // adding item to table
        int rowNum = tableSearch->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(stA->getName());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        tableSearch->insertRow(rowNum);
        tableSearch->setItem(rowNum, 0, newItem);

        // stations
        out << "p" << i << " = new ymaps.Placemark([" << stA->getLatitude() << ", " << stA->getLongitude() << "], {" << endl;
        out << "    hintContent: '" << stA->getName().toStdString() << "'," << endl;
        out << "    balloonContent: '" << stA->getName().toStdString() << "'," << endl;
        out << "}, {" << endl;
        out << "    preset: '" << getStationColor(stA->getType()) << "'" << endl;
        out << "});" << endl;
        out << jsMapVar << ".geoObjects.add(p" << i << ");" << endl;

        // links
        out << "l" << i << " = new ymaps.GeoObject({" << endl;
        out << "    geometry: {" << endl;
        out << "        type: \"LineString\"," << endl;
        out << "        coordinates: [" << endl;
        out << "            [" << stA->getLatitude() << ", " << stA->getLongitude() << "]," << endl;
        out << "            [" << stB->getLatitude() << ", " << stB->getLongitude() << "]" << endl;
        out << "        ]" << endl;
        out << "    }," << endl;
        out << "    properties:{" << endl;
        out << "        hintContent: \"" << stA->getName().toStdString() << " - " << stB->getName().toStdString() << "\"," << endl;
        out << "        balloonContent: \"" << stA->getName().toStdString() << " - " << stB->getName().toStdString() << "\"" << endl;
        out << "    }" << endl;
        out << "}, {" << endl;
        out << "    draggable: false," << endl;
        out << "    strokeColor: \"" << getLineColor(stA->getType(), stB->getType()) << "\"," << endl;
        out << "    strokeWidth: 5" << endl;
        out << "});" << endl;
        out << jsMapVar << ".geoObjects.add(l" << i << ");" << endl;
    }

    if (roads.size() > 0) {
        Road r = roads[roads.size() - 1];
        Station *lastStation = r.getEnd();
        out << "p" << roads.size() << " = new ymaps.Placemark([" << lastStation->getLatitude() << ", " << lastStation->getLongitude() << "], {" << endl;
        out << "    hintContent: '" << lastStation->getName().toStdString() << "'," << endl;
        out << "    balloonContent: '" << lastStation->getName().toStdString() << "'," << endl;
        out << "}, {" << endl;
        out << "    preset: '" << getStationColor(lastStation->getType()) << "'" << endl;
        out << "});" << endl;
        out << jsMapVar << ".geoObjects.add(p" << roads.size() << ");" << endl;

        // adding item to table
        int rowNum = tableSearch->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(lastStation->getName());
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        tableSearch->insertRow(rowNum);
        tableSearch->setItem(rowNum, 0, newItem);
    }

    htmlFooter(out);
    out.close();
}

std::string MapCreator::getStationColor(int stationType)
{
    switch (stationType) {
    case 0:
        return "twirl#blueIcon";
    case 1:
        return "twirl#redIcon";
    case 2:
        return "twirl#violetIcon";
    default:
        return "twirl#blueIcon";
    }
}

std::string MapCreator::getLineColor(int startStationType, int endStationType)
{
    if (startStationType == 0 && endStationType == 0) {
        return "#42aaff";
    }
    if (startStationType == 1 && endStationType == 1) {
        return "#ff0000";
    }
    if ((startStationType == 0 && endStationType == 2) || (startStationType == 2 && endStationType == 0)) {
        return "#42aaff";
    }
    if ((startStationType == 1 && endStationType == 2) || (startStationType == 2 && endStationType == 1)) {
        return "#ff0000";
    }
    return "#000000";
}

void MapCreator::htmlHeader(ofstream& out)
{
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" << htmlTitle << "</title>" << endl;
    out << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />" << endl;
    out << "<script src=\"" << mapApiUrl << "\" type=\"text/javascript\"></script>" << endl;
    out << "<style type=\"text/css\">" << endl;
    out << "    html {height:100%}" << endl;
    out << "    body {height:100%;margin:0px;padding:0px}" << endl;
    out << "    #map {width: 100%; height:100%}" << endl;
    out << "</style>" << endl;
    out << "<script type=\"text/javascript\">" << endl;
    out << "ymaps.ready(init);" << endl;
    out << "var myMap;" << endl << endl;
    out << "function init(){" << endl;
    out << "    " << jsMapVar << " = new ymaps.Map (\"map\", {" << endl;
    out << "        center: [" << mapCenterLat << ", " << mapCenterLon << "]," << endl;
    out << "        zoom: 8," << endl;
    out << "        behaviors:['default', 'scrollZoom']" << endl;
    out << "    });" << endl;
    out << "    " << jsMapVar << ".controls.add(" << endl;
    out << "        new ymaps.control.ZoomControl()" << endl;
    out << "    );" << endl;
}

void MapCreator::htmlFooter(ofstream& out)
{
    out << "}" << endl;
    out << "</script>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<div id=\"map\"></div>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;
}
