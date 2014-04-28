#include "cannot_open_file_exception.h"

CannotOpenFileException::CannotOpenFileException(const QString& filename):
    _filename(filename)
{

}

CannotOpenFileException::~CannotOpenFileException()
{

}

QString CannotOpenFileException::getMsg() const
{
    return "Не удалось открыть файл " + _filename;
}
