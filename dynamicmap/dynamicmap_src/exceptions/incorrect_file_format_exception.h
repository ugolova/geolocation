#ifndef INCORRECT_FILE_FORMAT_EXCEPTION_H
#define INCORRECT_FILE_FORMAT_EXCEPTION_H

#include "dynamicmap_exception.h"

class IncorrectFileFormatException: public DynamicMapException
{
public:
   IncorrectFileFormatException(const QString& lineNumber);
  ~IncorrectFileFormatException();
   QString getMsg() const;
private:
   QString _lineNumber;
};

#endif // INCORRECT_FILE_FORMAT_EXCEPTION_H
