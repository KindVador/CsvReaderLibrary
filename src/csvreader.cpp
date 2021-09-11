#include "csvreader.hpp"

CsvReader::CsvReader(QString filePath, QChar separator, QChar comment):
    _file(filePath), _separator(separator), _comments(comment)
{

}

CsvReader::~CsvReader()
{

}

QChar CsvReader::separator() const
{
    return _separator;
}

void CsvReader::setSeparator(const QChar &separator)
{
    _separator = separator;
}

QChar CsvReader::comments() const
{
    return _comments;
}

void CsvReader::setComments(const QChar &comments)
{
    _comments = comments;
}
