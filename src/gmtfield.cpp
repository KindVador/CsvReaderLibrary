#include "gmtfield.hpp"

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

    int hh = int(rest / HOUR_IN_MICRO);
    rest %= HOUR_IN_MICRO;

    int mm = int(rest / MINUTE_IN_MICRO);
    rest %= MINUTE_IN_MICRO;

    int ss = int(rest / SEC_IN_MICRO);
    rest %= SEC_IN_MICRO;

    int ms = int(rest / MILLI_IN_MICRO);

    int mms = int(rest % MILLI_IN_MICRO);

    if (mms == 0) {
        if (ms == 0) {
            return QString("%1-%2:%3:%4").arg(yd, 3, 10, QChar('0')).arg(hh, 2, 10, QChar('0')).arg(mm, 2, 10, QChar('0')).arg(ss, 2, 10, QChar('0'));
        } else {
            return QString("%1-%2:%3:%4-%5").arg(yd, 3, 10, QChar('0')).arg(hh, 2, 10, QChar('0')).arg(mm, 2, 10, QChar('0')).arg(ss, 2, 10, QChar('0')).arg(ms, 3, 10, QChar('0'));
        }
    } else {
        return QString("%1-%2:%3:%4-%5.%6").arg(yd, 3, 10, QChar('0')).arg(hh, 2, 10, QChar('0')).arg(mm, 2, 10, QChar('0')).arg(ss, 2, 10, QChar('0')).arg(ms, 3, 10, QChar('0')).arg(mms, 3, 10, QChar('0'));
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
