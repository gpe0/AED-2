#include "Trip.h"

Trip::Trip() {
    distance = 0;
    difZones = 0;
}

Trip::Trip(std::list<Stop> stopsPath, std::list<Line> linesPath, double distance, int difZones) {
    this->stopsPath = stopsPath;
    this->linesPath = linesPath;
    this->distance = distance;
    this->difZones = difZones;
}

std::list<Stop> Trip::getStopsPath() {
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

Trip &Trip::operator=(const Trip &trip) {
    stopsPath = trip.stopsPath;
    linesPath = trip.linesPath;
    distance = trip.distance;
    difZones = trip.difZones;
    return *this;
}
