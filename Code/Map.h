#ifndef AED_2_MAP_H
#define AED_2_MAP_H

#include <string>
#include "Stop.h"

class Map {
private:
    std::string html;
public:
    Map();
    void addConnection(Stop& stop1, Stop& stop2);
    void addStop(Stop& stop);
    std::string getHTML();
    class InvalidMap {
    private:
        std::string msg;
    public:
        InvalidMap(std::string msg) {this->msg = msg;};
        std::string what() const {return msg;};
    };
};


#endif
