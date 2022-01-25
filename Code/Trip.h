#ifndef AED_2_TRIP_H
#define AED_2_TRIP_H

#include <string>
#include <list>
#include "Line.h"

class Trip {
    std::list<std::string> stopsPath;
    std::list<Line> linesPath;
    double distance;
    int difZones;

public:
    Trip(std::list<std::string> stopsPath, std::list<Line> linesPath, double distance, int difZones);

    std::list<std::string> getStopsPath();
    std::list<Line> getLinesPath();
    double getDistance();
    int getDifZones();
};


#endif
