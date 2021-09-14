#pragma once

#include "field.hpp"
#include <QString>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QTimeZone>

static qint64 SEC_IN_MICRO = 1000000L;
static qint64 MILLI_IN_MICRO = 1000L;
static qint64 DAY_IN_MICRO = 86400000000L;
static qint64 HOUR_IN_MICRO = 3600000000L;
static qint64 MINUTE_IN_MICRO = 60000000L;

class GmtField : public Field {

public:
    // constructors
    GmtField() = default;
    explicit GmtField(qint64 value, int year=1970);

    // destructor
    ~GmtField() = default;

    // classmethods
    static GmtField fromDateTime(const QDateTime &dt);
    static GmtField fromString(const QString &str, const QString &format);

    // Getter & Setter
    [[nodiscard]] int getYear() const;
    void setYear(int year);
    [[nodiscard]] qint64 getValue() const;

    // methods
    [[nodiscard]] QDateTime toDateTime(const QTimeZone &tz=QTimeZone::utc()) const;
    [[nodiscard]] qint64 toTimeStamp() const;
    [[nodiscard]] QString toString() const override;
    [[nodiscard]] std::string toStdString() const override;
    [[nodiscard]] QDate getDate() const;
    [[nodiscard]] QTime getTime() const;

private:
    long long int _value = 0;
    int _year = 1970;
};
