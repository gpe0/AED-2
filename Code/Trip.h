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
    /**Instantiates a trip with no stops, no lines, zero distance and zones
     *
     */
    Trip();

    /**Instantiates a trip given a stop path, line path, distance and zones
     *
     * @param stopsPath stop path
     * @param linesPath line path
     * @param distance distance
     * @param difZones zones
     */
    Trip(std::list<Stop> stopsPath, std::list<Line> linesPath, double distance, int difZones);

    /**Returns trip's stop path
     *
     * @return stop path
     */
    std::list<Stop> getStopsPath();

    /**Returns trip's line path
     *
     * @return line path
     */
    std::list<Line> getLinesPath();

    /**Returns trip's distance
     *
     * @return distance
     */
    double getDistance();

    /**Returns trip's zones
     *
     * @return zones
     */
    int getDifZones();

    Trip& operator=(const Trip& trip);
};


#endif
