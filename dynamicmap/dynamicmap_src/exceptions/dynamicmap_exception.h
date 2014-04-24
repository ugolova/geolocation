#ifndef DYNAMIC_MAP_EXCEPTION_H
#define DYNAMIC_MAP_EXCEPTION_H

#include <QString>

class DynamicMapException
{
public:
   virtual QString getMsg() const = 0;
};

#endif // DYNAMIC_MAP_EXCEPTION_H
