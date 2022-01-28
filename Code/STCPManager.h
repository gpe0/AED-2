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
    STCPManager(int choice, double walkableBeetweenStops, double walkableToFromStops, bool nightShift);
    double distanceBetweenTwoPoints(double lat1, double lon1, double lat2, double lon2);
    void generateGraph();
    void clearGraph();
    void setChoice(int choice);
    void setWalkableBetweenStops(double walkableBeetweenStops);
    void setWalkableToFromStops(double walkableToFromStops);
    Trip pathBetweenStops(string a, string b); // 1 - best distance // 2 - fewer lines
    Trip pathBetweenStops(double lat1, double lon1, string b);
    Trip pathBetweenStops(double lat1, double lon1, double lat2, double lon2);
    Trip pathBetweenStops(string a, double lat2, double lon2);
    ~STCPManager();
};


#endif
