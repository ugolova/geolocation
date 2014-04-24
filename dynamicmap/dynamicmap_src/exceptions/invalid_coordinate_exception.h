#ifndef INVALID_COORDINATE_EXCEPTION_H
#define INVALID_COORDINATE_EXCEPTION_H

#include "dynamicmap_exception.h"

class InvalidCoordinateException: public DynamicMapException
{
public:
   InvalidCoordinateException(const QString& type, const QString& value);
  ~InvalidCoordinateException();
   QString getMsg() const;
private:
   QString _type;
   QString _value;
};

#endif // INVALID_COORDINATE_EXCEPTION_H
