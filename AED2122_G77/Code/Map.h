#ifndef AED_2_MAP_H
#define AED_2_MAP_H

#include <string>
#include "Stop.h"

class Map {
private:
    std::string html;
public:
    /**Instantiates a map
     *
     */
    Map();

    /**Adds a route between two stops in the map
     *
     * @param stop1 stop 1
     * @param stop2 stop 2
     */
    void addConnection(Stop& stop1, Stop& stop2);

    /**Adds a stop in the map
     *
     * @param stop stop
     */
    void addStop(Stop& stop);

    /**Returns the current map
     *
     * @return map
     */
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
