//
// Created by Florian Contival on 10/09/2021.
//

#ifndef CSVREADER_GMTFIELD_HPP
#define CSVREADER_GMTFIELD_HPP

#include <QDateTime>

class GmtField {
public:
    GmtField() = default;
    ~GmtField() = default;

    QDateTime toDateTime();

private:
    long long _timestamp = 0;
};


#endif //CSVREADER_GMTFIELD_HPP
