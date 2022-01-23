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
    ReadCsv reader;
    Graph *stops;
    map<string, int> codeToInt;
    vector<Stop> stopList;
    vector<Line> lineList;

public:
    STCPManager();
    double distanceBeetweenTwoPoints(double lat1, double lon1, double lat2, double lon2);
    void generateGraph();
    Trip pathBeetweenStops(string a, string b, int choice = 1); // 1 - best distance // 2 - fewer lines
    Trip pathBeetweenStops(double lat1, double lon1, string b, double walkable, int choice = 1);
    Trip pathBeetweenStops(double lat1, double lon1, double lat2, double lon2, double walkable, int choice = 1);
    Trip pathBeetweenStops(string a, double lat2, double lon2, double walkable, int choice = 1);
    ~STCPManager();
};


#endif
