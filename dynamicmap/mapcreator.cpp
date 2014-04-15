#include "mapcreator.h"

const string MapCreator::MAP_FILENAME = "map.html";
const string MapCreator::HTML_TITLE = "DynamicMap";
const string MapCreator::MAP_API_URL = "http://api-maps.yandex.ru/2.0-stable/?load=package.full&lang=ru-RU";
const string MapCreator::JS_MAP_VAR = "myMap";
const double MapCreator::MAP_CENTER_LAT = 59.938531;
const double MapCreator::MAP_CENTER_LON = 30.313497;

MapCreator::MapCreator()
{
}

const char* MapCreator::getMapFilename()
{
    return MAP_FILENAME.c_str();
}

void MapCreator::writeHTML()
{
    ofstream out;
    out.open(MAP_FILENAME.c_str());
    out << "<!DOCTYPE html>" << endl;
    out << "<html>" << endl;
    out << "<head>" << endl;
    out << "<title>" << HTML_TITLE << "</title>" << endl;
    out << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />" << endl;
    out << "<script src=\"" << MAP_API_URL << "\" type=\"text/javascript\"></script>" << endl;
    out << "<style type=\"text/css\">" << endl;
    out << "    html {height:100%}" << endl;
    out << "    body {height:100%;margin:0px;padding:0px}" << endl;
    out << "    #map {width: 100%; height:100%}" << endl;
    out << "</style>" << endl;
    out << "<script type=\"text/javascript\">" << endl;
    out << "ymaps.ready(init);" << endl;
    out << "var myMap;" << endl << endl;
    out << "function init(){" << endl;
    out << "    " << JS_MAP_VAR << " = new ymaps.Map (\"map\", {" << endl;
    out << "        center: [" << MAP_CENTER_LAT << ", " << MAP_CENTER_LON << "]," << endl;
    out << "        zoom: 8," << endl;
    out << "        behaviors:['default', 'scrollZoom']" << endl;
    out << "    });" << endl;
    out << "    " << JS_MAP_VAR << ".controls.add(" << endl;
    out << "        new ymaps.control.ZoomControl()" << endl;
    out << "    );" << endl;
    /*
                p1 = new ymaps.Placemark([59.991686, 30.221030], {
                    hintContent: 'Яхтенная',
                    balloonContent: 'Станция "Яхтенная"'
                });
                p2 = new ymaps.Placemark([59.989260, 30.255280], {
                    hintContent: 'Старая Деревня',
                    balloonContent: 'Станция "Старая Деревня"'
                });
                p3 = new ymaps.Placemark([60.008344, 30.258577], {
                    hintContent: 'Комендантский проспект',
                    balloonContent: 'Станция "Комендантский проспект"'
                });

                l12 = new ymaps.GeoObject({
                    geometry: {
                        type: "LineString",
                        coordinates: [
                            [59.991686, 30.221030],
                            [59.989260, 30.255280]
                        ]
                    },
                    properties:{
                        hintContent: "Яхтенная - Старая Деревня",
                        balloonContent: "Яхтенная - Старая Деревня"
                    }
                }, {
                    draggable: false,
                    strokeColor: "#00ff00",
                    strokeWidth: 5
                });

                l23 = new ymaps.GeoObject({
                    geometry: {
                        type: "LineString",
                        coordinates: [
                            [59.989260, 30.255280],
                            [60.008344, 30.258577]
                        ]
                    },
                    properties:{
                        hintContent: "Старая Деревня - Комендантский проспект",
                        balloonContent: "Старая Деревня - Комендантский проспект"
                    }
                }, {
                    draggable: false,
                    strokeColor: "#0000ff",
                    strokeWidth: 5
                });

                myMap.geoObjects.add(p1).add(p2).add(p3);
                myMap.geoObjects.add(l12).add(l23);
    */
    out << "}" << endl;
    out << "</script>" << endl;
    out << "</head>" << endl;
    out << "<body>" << endl;
    out << "<div id=\"map\"></div>" << endl;
    out << "</body>" << endl;
    out << "</html>" << endl;

    out.close();
}

void MapCreator::addStation(ofstream out)
{

}

void MapCreator::addLink(ofstream out)
{

}
