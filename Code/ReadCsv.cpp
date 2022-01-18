#include "ReadCsv.h"

void ReadCsv::readStops(string file) {
    string content;
    ifstream myFile(file);
    getline(myFile, content);
    while (getline(myFile, content, ',')) {
        stops.push_back(content);

    }
}

void ReadCsv::readLine(string code, string dir) {
    string content;
    file = "../Dataset/line_" + code + "_" + dir + ".csv";

    ifstream  myFile(file);

    while (getline(myFile, content)) {
        line.push_back(content);
    }
}


void ReadCsv::getStops() {
    for (size_t i = 0; i < stops.size(); i++) {
        cout << stops[i] << endl;
    }
}

void ReadCsv::getLine() {
    for (size_t i = 0; i < line.size(); i++) {
        cout << line[i] << endl;
    }
}