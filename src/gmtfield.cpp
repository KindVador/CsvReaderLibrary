#include "gmtfield.hpp"

static long long int SEC_IN_MICRO = 1000000L;
static long long int MILLI_IN_MICRO = 1000L;
static long long int DAY_IN_MICRO = 86400000000L;
static long long int HOUR_IN_MICRO = 3600000000L;
static long long int MINUTE_IN_MICRO = 60000000L;

GmtField::GmtField(long long int value): _value(value) {
}

QDateTime GmtField::toDateTime() const {

    return QDateTime();
}

GmtField GmtField::fromString(QString str, QString format) {


    return GmtField();
}

QString GmtField::toString() const {
    int yd = int(_value / DAY_IN_MICRO + 1);
    long long int rest = _value % DAY_IN_MICRO;

    int hh = rest / HOUR_IN_MICRO;
    rest %= HOUR_IN_MICRO;

    int mm = rest / MINUTE_IN_MICRO;
    rest %= MINUTE_IN_MICRO;

    int ss = rest / SEC_IN_MICRO;
    rest %= SEC_IN_MICRO;

    int ms = rest / MILLI_IN_MICRO;

    int mms = rest % MILLI_IN_MICRO;

    if (mms == 0) {
        if (ms == 0) {
            QString str = QString("%03d-%02d:%02d:%02d");
            return str.arg(QString::number(yd), QString::number(hh), QString::number(mm), QString::number(ss));
        } else {
            QString str = QString("%03d-%02d:%02d:%02d-%03d");
            return str.arg(QString::number(yd), QString::number(hh), QString::number(mm), QString::number(ss), QString::number(ms));
        }
    } else {
        QString str = QString("%03d-%02d:%02d:%02d-%03d.%03d");
        return str.arg(QString::number(yd), QString::number(hh), QString::number(mm), QString::number(ss), QString::number(ms), QString::number(mms));
    }
}

std::string GmtField::toStdString() const {
    return toString().toStdString();
}

GmtField GmtField::fromDateTime(QDateTime dt) {

    return GmtField();
}

bool GmtField::isGmt(QString str) {

    return false;
}

long long int GmtField::toTimeStamp() const {
    return _value;
}
