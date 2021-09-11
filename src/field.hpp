//
// Created by Florian Contival on 11/09/2021.
//

#ifndef CSVREADER_FIELD_HPP
#define CSVREADER_FIELD_HPP

#include <QString>

class Field {
public:
    virtual QString toString() const = 0;
    virtual std::string toStdString() const = 0;
};


#endif //CSVREADER_FIELD_HPP
