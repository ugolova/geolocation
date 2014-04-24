#include "unknown_station_exception.h"

UnknownStationException::UnknownStationException(const QString& station):
    _station(station)
{

}

UnknownStationException::~UnknownStationException()
{

}

QString UnknownStationException::getMsg() const
{
    return "Станция \"" + _station + "\" не найдена!";
}
