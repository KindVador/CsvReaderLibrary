#pragma once

#include <QDateTime>

class GmtField {
public:
    GmtField() = default;
    ~GmtField() = default;

    QDateTime toDateTime();

private:
    long long _timestamp = 0;
};
