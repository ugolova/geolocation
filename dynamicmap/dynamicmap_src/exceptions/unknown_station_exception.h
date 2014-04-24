#ifndef UNKNOWN_STATION_EXCEPTION_H
#define UNKNOWN_STATION_EXCEPTION_H

#include "dynamicmap_exception.h"

class UnknownStationException: public DynamicMapException
{
public:
   UnknownStationException(const QString& station);
  ~UnknownStationException();
   QString getMsg() const;
private:
   QString _station;
};

#endif // UNKNOWN_STATION_EXCEPTION_H
