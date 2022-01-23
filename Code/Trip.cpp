#include "Trip.h"

Trip::Trip(std::list<std::string> stopsPath, std::list<Line> linesPath, double distance) {
    this->stopsPath = stopsPath;
    this->linesPath = linesPath;
    this->distance = distance;
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
