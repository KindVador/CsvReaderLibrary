#pragma once
#include <QFile>
#include <QChar>

class CsvReader
{
public:
    CsvReader() = default;
    CsvReader(const QString &filePath, QChar separator, QChar comment);
    ~CsvReader() = default;

    [[nodiscard]] QChar separator() const;
    void setSeparator(const QChar &separator);

    [[nodiscard]] QChar comments() const;
    void setComments(const QChar &comments);

private:
    QFile _file;
    QChar _separator;
    QChar _comments;

};
