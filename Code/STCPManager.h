#ifndef AED_2_STCPMANAGER_H
#define AED_2_STCPMANAGER_H

#include <map>
#include "Graph.h"
#include "ReadCsv.h"
#include "Stop.h"
#include "Line.h"
#include "Trip.h"

class STCPManager {
private:
    int choice;
    double walkableBetweenStops;
    double walkableToFromStops;
    ReadCsv reader;
    Graph *stops;
    map<string, int> codeToInt;
    vector<Stop> stopList;
    vector<Line> lineList;

public:
    /**Instantiates a STCP manager given a user's choice, walkable kilometers between stops, walkable kilometers to and from stops and a shift
     *
     * @param choice user's choice
     * @param walkableBetweenStops walkable kilometers between stops
     * @param walkableToFromStops walkable kilometers to and from stops
     * @param nightShift if it is a night shift or not
     */
    STCPManager(int choice, double walkableBetweenStops, double walkableToFromStops, bool nightShift);

    /**Returns the distance between two points
     *
     * @param lat1 latitude 1
     * @param lon1 longitude 1
     * @param lat2 latitude 2
     * @param lon2 longitude 2
     * @return distance
     */
    double distanceBetweenTwoPoints(double lat1, double lon1, double lat2, double lon2);

    /**Generates the STCP graph (n^2)
     *
     */
    void generateGraph();

    /**Returns the best trip between two stops (n^2 - if bfs is used n*log(n) otherwise)
     *
     * @param a stop 1
     * @param b stop 2
     * @return best trip
     */
    Trip pathBetweenStops(string a, string b);

    /**Returns the best trip between a location (begin) and a stop (n^3 - if bfs is used (n^2)*log(n) otherwise)
     *
     * @param lat1 latitude 1
     * @param lon1 longitude 1
     * @param b stop 2
     * @return best trip
     */
    Trip pathBetweenStops(double lat1, double lon1, string b);

    /**Returns the best trip between two locations (n^4 - if bfs is used (n^3)*log(n) otherwise)
     *
     * @param lat1 latitude 1
     * @param lon1 longitude 1
     * @param lat2 latitude 2
     * @param lon2 longitude 2
     * @return best trip
     */
    Trip pathBetweenStops(double lat1, double lon1, double lat2, double lon2);

    /**Returns the best trip between a location (end) and a stop (n^3 - if bfs is used (n^2)*log(n) otherwise)
     *
     * @param a stop 1
     * @param lat2 latitude 2
     * @param lon2 longitude 2
     * @return best trip
     */
    Trip pathBetweenStops(string a, double lat2, double lon2);

    /**Deletes the created graph
     *
     */
    ~STCPManager();
};


#endif
