#include "csvreader.hpp"

CsvReader::CsvReader(const QString &filePath, QChar separator, QChar comment):
    _file(filePath), _separator(separator), _comments(comment)
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
