#pragma once

#include "field.hpp"
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTimeZone>

static long long int SEC_IN_MICRO = 1000000L;
static long long int MILLI_IN_MICRO = 1000L;
static long long int DAY_IN_MICRO = 86400000000L;
static long long int HOUR_IN_MICRO = 3600000000L;
static long long int MINUTE_IN_MICRO = 60000000L;

class GmtField : public Field {

public:
    // constructors
    GmtField() = default;
    explicit GmtField(long long int value, int year=1970);

    // destructor
    ~GmtField() = default;

    // classmethods
    static GmtField fromDateTime(const QDateTime &dt);
    static GmtField fromString(const QString &str, const QString &format);

    // Getter & Setter
    [[nodiscard]] int getYear() const;
    void setYear(int year);
    [[nodiscard]] long long int getValue() const;

    // methods
    [[nodiscard]] QDateTime toDateTime(const QTimeZone &tz=QTimeZone::utc()) const;
    [[nodiscard]] long long int toTimeStamp() const;
    [[nodiscard]] QString toString() const override;
    [[nodiscard]] std::string toStdString() const override;
    [[nodiscard]] QDate getDate() const;
    [[nodiscard]] QTime getTime() const;

private:
    long long int _value = 0;
    int _year = 1970;
};
