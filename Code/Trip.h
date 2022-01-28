#ifndef AED_2_TRIP_H
#define AED_2_TRIP_H

#include <string>
#include <list>
#include "Line.h"
#include "Stop.h"

class Trip {
    std::list<Stop> stopsPath;
    std::list<Line> linesPath;
    double distance;
    int difZones;

public:
    Trip();
    Trip(std::list<Stop> stopsPath, std::list<Line> linesPath, double distance, int difZones);

    std::list<Stop> getStopsPath();
    std::list<Line> getLinesPath();
    double getDistance();
    int getDifZones();

    Trip& operator=(const Trip& trip);
};


#endif
