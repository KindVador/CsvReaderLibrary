#pragma once

#include "field.hpp"
#include <QString>
#include <QDateTime>

static long long int SEC_IN_MICRO = 1000000L;
static long long int MILLI_IN_MICRO = 1000L;
static long long int DAY_IN_MICRO = 86400000000L;
static long long int HOUR_IN_MICRO = 3600000000L;
static long long int MINUTE_IN_MICRO = 60000000L;

class GmtField : public Field {

public:
    // constructors
    GmtField() = default;
    explicit GmtField(long long int value);

    // destructor
    ~GmtField() = default;

    // classmethods
    static bool isGmt(QString str);
    static GmtField fromDateTime(QDateTime dt);
    static GmtField fromString(QString str, QString format);

    // methods
    QDateTime toDateTime() const;
    [[nodiscard]] long long int toTimeStamp() const;
    [[nodiscard]] QString toString() const override;
    [[nodiscard]] std::string toStdString() const override;

private:
    long long int _value = 0;
};
