#ifndef UNKNOWN_LINK_EXCEPTION_H
#define UNKNOWN_LINK_EXCEPTION_H

#include "dynamicmap_exception.h"

class UnknownLinkException: public DynamicMapException
{
public:
   UnknownLinkException(const QString& stationA, const QString& stationB, const double& distance);
  ~UnknownLinkException();
   QString getMsg() const;
private:
   QString _stationA;
   QString _stationB;
   double _distance;
};

#endif // UNKNOWN_LINK_EXCEPTION_H
