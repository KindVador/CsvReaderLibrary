#include "gmtfield.hpp"


GmtField::GmtField(long long int value, int year): _value(value), _year(year) {
}

QDateTime GmtField::toDateTime(const QTimeZone &tz) const {
    return {getDate(), getTime(), tz};
}

GmtField GmtField::fromString(const QString &str, const QString &format) {
    return {};
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

GmtField GmtField::fromDateTime(const QDateTime &dt) {
    if (!dt.isValid())
        return {};
    int year = dt.date().year();
    long long int value = dt.toMSecsSinceEpoch() - QDateTime(QDate(year, 1, 1), QTime(0,0,0), dt.timeZone()).toMSecsSinceEpoch();
    // as QDateTime has a precision of 1 millisecond we need to multiply the value by 1000 to convert into microsecond
    value *= 1000;
    return GmtField(value, year);
}

long long int GmtField::toTimeStamp() const {
    // TODO
    return _value;
}

int GmtField::getYear() const {
    return _year;
}

void GmtField::setYear(int year) {
    _year = year;
}

QDate GmtField::getDate() const {
    int yd = int(_value / DAY_IN_MICRO);
    return QDate(getYear(), 1, 1).addDays(yd);
}

QTime GmtField::getTime() const {
    long long int rest = _value % DAY_IN_MICRO;

    int hh = int(rest / HOUR_IN_MICRO);
    rest %= HOUR_IN_MICRO;

    int mm = int(rest / MINUTE_IN_MICRO);
    rest %= MINUTE_IN_MICRO;

    int ss = int(rest / SEC_IN_MICRO);
    rest %= SEC_IN_MICRO;

    int ms = int(rest / MILLI_IN_MICRO);

    return {hh, mm, ss, ms};
}

long long int GmtField::getValue() const {
    return _value;
}
