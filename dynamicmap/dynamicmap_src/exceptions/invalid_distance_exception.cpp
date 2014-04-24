#include "invalid_distance_exception.h"

InvalidDistanceException::InvalidDistanceException(const QString& value):
    _value(value)
{

}

InvalidDistanceException::~InvalidDistanceException()
{

}

QString InvalidDistanceException::getMsg() const
{
    return "Некорректное расстояние: " + _value;
}
