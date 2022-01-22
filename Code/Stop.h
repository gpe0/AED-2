#ifndef AED_2_STOP_H
#define AED_2_STOP_H


#include <string>

class Stop {
    std::string code, name, zone;
    double latitude, longitude;

public:
    Stop(std::string code, std::string name, std::string zone, double latitude, double longitude);

    std::string getCode();
    std::string getName();
    std::string getZone();
    double getLatitude();
    double getLongitude();
};


#endif
