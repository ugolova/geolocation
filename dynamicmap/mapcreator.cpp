#include "mapcreator.h"

MapCreator::MapCreator(MapMode mode):
    container(NULL)
{
    this->mode = mode;
    mapFilePath = (QDir::toNativeSeparators(QDir::tempPath()) + QDir::separator()).toStdString() + "dynamicmap_";
    htmlTitle = "DynamicMap";
    switch (this->mode) {
    case SEARCH:
        mapFilePath += "search";
        htmlTitle += "Search";
        break;
    case STATIONS:
        mapFilePath += "stations";
        htmlTitle += "Stations";
        break;
    case LINKS:
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

const char* MapCreator::getMapFilePath()
{
    return mapFilePath.c_str();
}

void MapCreator::makeHTML()
{
    ofstream out;
    out.open(mapFilePath.c_str());
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

    addStations(out);
    if (mode == LINKS) {
        addLinks(out);
    }

    out << "}" << endl;
    out << "</script>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<div id=\"map\"></div>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;

    out.close();
}

void MapCreator::setContainer(MultiGraph<double, Station> *container)
{
    this->container = container;
}

MultiGraph<double, Station>* MapCreator::getContainer()
{
    return container;
}

void MapCreator::addStations(ofstream& out)
{
    if (container != NULL) {
        DynamicArray<Station> *arr = container->getVertexs();
        for (int i = 0; i < arr->getSize(); i++) {
            Station *st = arr->get(i);
            out << "p" << i << " = new ymaps.Placemark([" << st->getLatitude() << ", " << st->getLongitude() << "], {" << endl;
            out << "    hintContent: '" << st->getName() << "'," << endl;
            out << "    balloonContent: '" << st->getName() << "'," << endl;
            out << "});" << endl;
            out << jsMapVar << ".geoObjects.add(p" << i << ");" << endl;
            qDebug() << st->getLatitude() << " " << st->getLongitude();
        }
    }
    /*
    int id = 1;
    out << "p" << id << " = new ymaps.Placemark([59.991686, 30.221030], {" << endl;
    out << "    hintContent: 'Яхтенная'," << endl;
    out << "    balloonContent: 'Яхтенная'," << endl;
    out << "});" << endl;
    out << jsMapVar << ".geoObjects.add(p" << id << ");" << endl;

    id = 2;
    out << "p" << id << " = new ymaps.Placemark([59.989260, 30.255280], {" << endl;
    out << "    hintContent: 'Старая Деревня'," << endl;
    out << "    balloonContent: 'Старая Деревня'," << endl;
    out << "});" << endl;
    out << jsMapVar << ".geoObjects.add(p" << id << ");" << endl;

    id = 3;
    out << "p" << id << " = new ymaps.Placemark([60.008344, 30.258577], {" << endl;
    out << "    hintContent: 'Комендантский проспект'," << endl;
    out << "    balloonContent: 'Комендантский проспект'," << endl;
    out << "});" << endl;
    out << jsMapVar << ".geoObjects.add(p" << id << ");" << endl;
    */
}

void MapCreator::addLinks(ofstream& out)
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
