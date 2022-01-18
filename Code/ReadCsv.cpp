#include "ReadCsv.h"

void ReadCsv::readStops(string file) {
    string content;
    ifstream myFile(file);
    getline(myFile, content);
    while (getline(myFile, content, ',')) {
        stops.push_back(content);

    }
    return;
}

void ReadCsv::getStops() {
    for (size_t i = 0; i < stops.size(); i++) {
        cout << stops[i] << endl;
    }
    return;
}