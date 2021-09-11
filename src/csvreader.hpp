#pragma once
#include <QFile>
#include <QChar>

class CsvReader
{
public:
    CsvReader() = default;
    CsvReader(QString filePath, QChar separator, QChar comment);
    ~CsvReader();

    QChar separator() const;
    void setSeparator(const QChar &separator);

    QChar comments() const;
    void setComments(const QChar &comments);

private:
    QFile _file;
    QChar _separator;
    QChar _comments;

};
