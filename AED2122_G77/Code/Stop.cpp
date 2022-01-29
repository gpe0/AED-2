#include "Stop.h"

using namespace std;

Stop::Stop(string code, string name, string zone, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->zone = zone;
    this->latitude = latitude;
    this->longitude = longitude;

}

string Stop::getCode() {
    return code;
}

string Stop::getName() {
    return name;
}

string Stop::getZone() {
    return zone;
}

double Stop::getLatitude() {
    return latitude;
}

double Stop::getLongitude() {
    return longitude;
}
