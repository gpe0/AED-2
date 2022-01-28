#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <string>

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
