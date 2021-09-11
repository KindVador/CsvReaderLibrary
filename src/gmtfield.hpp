#pragma once

#include "field.hpp"
#include <QString>
#include <QDateTime>

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
