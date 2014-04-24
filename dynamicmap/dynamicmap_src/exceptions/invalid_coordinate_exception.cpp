#include "invalid_coordinate_exception.h"

InvalidCoordinateException::InvalidCoordinateException(const QString& type, const QString& value):
    _type(type),
    _value(value)
{

}

InvalidCoordinateException::~InvalidCoordinateException()
{

}

QString InvalidCoordinateException::getMsg() const
{
    return "Некорректная " + _type + ": " + _value;
}
