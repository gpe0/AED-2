#include <iostream>
#include "Code/STCPManager.h"

using namespace std;

int main() {
    cout << "AED 2021/2022 - Projeto 2" << endl;

    STCPManager manager(4, 0.05, 0.5);

    manager.generateGraph();

    //Trip res = manager.pathBeetweenStops("CUS4", "ESED2");

    //Trip  res = manager.pathBeetweenStops(41.20572900, -8.64556100, "HSJ11");

    Trip  res = manager.pathBeetweenStops(41.20572900, -8.64556100, 41.1780, -8.5980);
    //Trip  res = manager.pathBeetweenStops(41.20113087451074, -8.665401509469909, 41.182674066775945, -8.68009820003988);
    //Trip  res = manager.pathBeetweenStops("CUS4", 41.1780, -8.5980);
    cout << res.getDistance() << endl;

    list<Line> lines = res.getLinesPath();
    auto lineIt = lines.begin();


    for (auto ele : res.getStopsPath()) {
        string line = "";
        if (lineIt != lines.end()) {
            line = " (" + lineIt->getCode() + ")";
            lineIt++;
        }
        cout << ele << line << " -> "<< flush;
    }
    cout << "arrived!" << endl;

}
