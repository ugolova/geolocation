#ifndef CANNOT_OPEN_FILE_EXCEPTION_H
#define CANNOT_OPEN_FILE_EXCEPTION_H

#include "dynamicmap_exception.h"

class CannotOpenFileException: public DynamicMapException
{
public:
   CannotOpenFileException(const QString& filename);
  ~CannotOpenFileException();
   QString getMsg() const;
private:
   QString _filename;
};

#endif // CANNOT_OPEN_FILE_EXCEPTION_H
