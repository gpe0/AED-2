#include <iostream>
#include "Code/STCPManager.h"

using namespace std;

int main() {
    cout << "AED 2021/2022 - Projeto 2" << endl;

    STCPManager manager;

    manager.generateGraph();

    //list<string> res = manager.pathBeetweenStops("CUS4", "HSJ11");

    //list<string> res = manager.pathBeetweenStops(41.20572900, -8.64556100, "HSJ11");

    //list<string> res = manager.pathBeetweenStops(41.20572900, -8.64556100, 41.1780, -8.5980);

    list<string> res = manager.pathBeetweenStops("CUS4", 41.1780, -8.5980);

    for (auto ele : res) {
        cout << ele << " -> "<< flush;
    }
    cout << "arrived!" << endl;

    return 0;
}
