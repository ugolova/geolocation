#include "unknown_link_exception.h"

UnknownLinkException::UnknownLinkException(const QString& stationA, const QString& stationB, const double &distance):
    _stationA(stationA),
    _stationB(stationB),
    _distance(distance)
{

}

UnknownLinkException::~UnknownLinkException()
{

}

QString UnknownLinkException::getMsg() const
{
    return "Связь \"" + _stationA + " - " + _stationB + " (" + QString::number(_distance) + ")\" не найдена!";
}
