#include "Trip.h"

Trip::Trip(std::list<std::string> stopsPath, std::list<Line> linesPath, double distance, int difZones) {
    this->stopsPath = stopsPath;
    this->linesPath = linesPath;
    this->distance = distance;
    this->difZones = difZones;
}

std::list<std::string> Trip::getStopsPath() {
    return stopsPath;
}

std::list<Line> Trip::getLinesPath() {
    return linesPath;
}

double Trip::getDistance() {
    return distance;
}

int Trip::getDifZones() {
    return difZones;
}
