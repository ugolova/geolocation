#ifndef INVALID_DISTANCE_EXCEPTION_H
#define INVALID_DISTANCE_EXCEPTION_H

#include "dynamicmap_exception.h"

class InvalidDistanceException: public DynamicMapException
{
public:
   InvalidDistanceException(const QString& value);
  ~InvalidDistanceException();
   QString getMsg() const;
private:
   QString _value;
};

#endif // INVALID_DISTANCE_EXCEPTION_H
