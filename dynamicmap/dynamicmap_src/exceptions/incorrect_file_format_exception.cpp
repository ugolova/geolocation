#include "incorrect_file_format_exception.h"

IncorrectFileFormatException::IncorrectFileFormatException(const QString& lineNumber):
    _lineNumber(lineNumber)
{

}

IncorrectFileFormatException::~IncorrectFileFormatException()
{

}

QString IncorrectFileFormatException::getMsg() const
{
    return "Ошибка во входном файле в строке " + _lineNumber;
}
