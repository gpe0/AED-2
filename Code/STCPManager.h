#ifndef AED_2_STCPMANAGER_H
#define AED_2_STCPMANAGER_H

#include <map>
#include "Graph.h"
#include "ReadCsv.h"
#include "Stop.h"
#include "Line.h"

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
    list<string> pathBeetweenStops(string a, string b);
    list<string> pathBeetweenStops(double lat1, double lon1, string b);
    list<string> pathBeetweenStops(double lat1, double lon1, double lat2, double lon2);
    list<string> pathBeetweenStops(string a, double lat2, double lon2);
    ~STCPManager();
};


#endif
