#include "mapcreator.h"

MapCreator::MapCreator(MapMode mode):
    container(NULL)
{
    this->mode = mode;
    mapFilePath = QDir::toNativeSeparators(QDir::tempPath()) + QDir::separator() + "dynamicmap_";
    htmlTitle = "DynamicMap";
    switch (this->mode) {
    case MAP_SEARCH:
        mapFilePath += "search";
        htmlTitle += "Search";
        break;
    case MAP_STATIONS:
        mapFilePath += "stations";
        htmlTitle += "Stations";
        break;
    case MAP_LINKS:
        mapFilePath += "links";
        htmlTitle += "Links";
        break;
    default:
        break;
    }
    mapFilePath += ".html";

    mapApiUrl = "http://api-maps.yandex.ru/2.0-stable/?load=package.full&lang=ru-RU";
    jsMapVar = "myMap";
    mapCenterLat = 59.938531;
    mapCenterLon = 30.313497;
}

QString MapCreator::getMapFilePath()
{
    return mapFilePath;
}

QString MapCreator::makeHTML(MakeMode makeMode)
{
    QString result = "";

    QFile file(mapFilePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

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

    if (makeMode == MAKE_DEFAULT) {
        addStations(out);
        if (mode == MAP_LINKS) {
           addLinks(out);
        }
    } else if (makeMode == MAKE_SHORTEST_PATH) {
        result = addShortestPath(out);
    }

    out << "}" << endl;
    out << "</script>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<div id=\"map\"></div>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;

    file.close();

    return result;
}

void MapCreator::setContainer(MultiGraph<double, Station> *container)
{
    this->container = container;
}

MultiGraph<double, Station>* MapCreator::getContainer()
{
    return container;
}

void MapCreator::addStations(QTextStream& out)
{
    if (container != NULL) {
        DynamicArray<Station> *arr = container->getVertexs();
        for (int i = 0; i < arr->getSize(); i++) {
            Station *st = arr->get(i);
            out << "p" << i << " = new ymaps.Placemark([" << st->getLatitude() << ", " << st->getLongitude() << "], {" << endl;
            out << "    hintContent: '" << QString::fromStdString(st->getName()) << "'," << endl;
            out << "    balloonContent: '" << QString::fromStdString(st->getName()) << "'," << endl;
            out << "});" << endl;
            out << jsMapVar << ".geoObjects.add(p" << i << ");" << endl;

            qDebug() << "Written to HTML - Station: " << QString::fromStdString(st->getName()) << ", "
                     << "Lat: " << st->getLatitude() << ", "
                     << "Lon: " << st->getLongitude();
        }
    }
}

void MapCreator::addLinks(QTextStream& out)
{
    int id = 12;
    out << "l" << id << " = new ymaps.GeoObject({" << endl;
    out << "    geometry: {" << endl;
    out << "        type: \"LineString\"," << endl;
    out << "        coordinates: [" << endl;
    out << "            [59.991686, 30.221030]," << endl;
    out << "            [59.989260, 30.255280]" << endl;
    out << "        ]" << endl;
    out << "    }," << endl;
    out << "    properties:{" << endl;
    out << "        hintContent: \"Яхтенная - Старая Деревня\"," << endl;
    out << "        balloonContent: \"Яхтенная - Старая Деревня\"" << endl;
    out << "    }" << endl;
    out << "}, {" << endl;
    out << "    draggable: false," << endl;
    out << "    strokeColor: \"#00ff00\"," << endl;
    out << "    strokeWidth: 5" << endl;
    out << "});" << endl;
    out << jsMapVar << ".geoObjects.add(l" << id << ");" << endl;

    id = 23;
    out << "l" << id << " = new ymaps.GeoObject({" << endl;
    out << "    geometry: {" << endl;
    out << "        type: \"LineString\"," << endl;
    out << "        coordinates: [" << endl;
    out << "            [59.989260, 30.255280]," << endl;
    out << "            [60.008344, 30.258577]" << endl;
    out << "        ]" << endl;
    out << "    }," << endl;
    out << "    properties:{" << endl;
    out << "        hintContent: \"Старая Деревня - Комендантский проспект\"," << endl;
    out << "        balloonContent: \"Старая Деревня - Комендантский проспект\"" << endl;
    out << "    }" << endl;
    out << "}, {" << endl;
    out << "    draggable: false," << endl;
    out << "    strokeColor: \"#0000ff\"," << endl;
    out << "    strokeWidth: 5" << endl;
    out << "});" << endl;
    out << jsMapVar << ".geoObjects.add(l" << id << ");" << endl;
}

QString MapCreator::addShortestPath(QTextStream& out)
{
    Station *start = ControllerGUI::getStationByName(container, pathStationA);
    Station *end = ControllerGUI::getStationByName(container, pathStationB);

    if (start != NULL && end != NULL) {
        double length = 0;
        std::vector<Road> roads = Algorithm::findShortestPath(container, start, end, length);

        for(std::vector<int>::size_type i = 0; i < roads.size(); i++) {

            Road r = roads[i];
            Station *stA = r.getStart();
            Station *stB = r.getEnd();

            // adding item to table
            int rowNum = tableSearch->rowCount();
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(stA->getName()));
            newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
            tableSearch->insertRow(rowNum);
            tableSearch->setItem(rowNum, 0, newItem);

            // stations
            out << "p" << i << " = new ymaps.Placemark([" << stA->getLatitude() << ", " << stA->getLongitude() << "], {" << endl;
            out << "    hintContent: '" << QString::fromStdString(stA->getName()) << "'," << endl;
            out << "    balloonContent: '" << QString::fromStdString(stA->getName()) << "'," << endl;
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
            out << "        hintContent: \"" << QString::fromStdString(stA->getName()) << " - " << QString::fromStdString(stB->getName()) << "\"," << endl;
            out << "        balloonContent: \"" << QString::fromStdString(stA->getName()) << " - " << QString::fromStdString(stB->getName()) << "\"" << endl;
            out << "    }" << endl;
            out << "}, {" << endl;
            out << "    draggable: false," << endl;
            out << "    strokeColor: \"#00ff00\"," << endl;
            out << "    strokeWidth: 5" << endl;
            out << "});" << endl;
            out << jsMapVar << ".geoObjects.add(l" << i << ");" << endl;
        }
        Road r = roads[roads.size() - 1];
        Station *lastStation = r.getEnd();
        out << "p" << roads.size() << " = new ymaps.Placemark([" << lastStation->getLatitude() << ", " << lastStation->getLongitude() << "], {" << endl;
        out << "    hintContent: '" << QString::fromStdString(lastStation->getName()) << "'," << endl;
        out << "    balloonContent: '" << QString::fromStdString(lastStation->getName()) << "'," << endl;
        out << "});" << endl;
        out << jsMapVar << ".geoObjects.add(p" << roads.size() << ");" << endl;

        // adding item to table
        int rowNum = tableSearch->rowCount();
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(lastStation->getName()));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        tableSearch->insertRow(rowNum);
        tableSearch->setItem(rowNum, 0, newItem);

        return QString("");

    } else if (start == NULL) {
        return pathStationA;
    } else {
        return pathStationB;
    }
}

void MapCreator::setPathStationA(QString name)
{
    pathStationA = name;
}

void MapCreator::setPathStationB(QString name)
{
    pathStationB = name;
}

void MapCreator::setTableSearch(QTableWidget *table)
{
    tableSearch = table;
}
