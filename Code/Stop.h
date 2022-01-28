#ifndef AED_2_STOP_H
#define AED_2_STOP_H


#include <string>

class Stop {
    std::string code, name, zone;
    double latitude, longitude;


public:
    /**Instantiates a stop given a code, name, zone, latitude and longitude
     *
     * @param code code
     * @param name name
     * @param zone zone
     * @param latitude latitude
     * @param longitude longitude
     */
    Stop(std::string code, std::string name, std::string zone, double latitude, double longitude);

    /**Returns stop's code
     *
     * @return code
     */
    std::string getCode();

    /**Returns stop's name
     *
     * @return name
     */
    std::string getName();

    /**Returns stop's zone
     *
     * @return zone
     */
    std::string getZone();

    /**Returns stop's latitude
     *
     * @return latitude
     */
    double getLatitude();

    /**Returns stop's longitude
     *
     * @return longitude
     */
    double getLongitude();
};


#endif
