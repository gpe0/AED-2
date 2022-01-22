#include <sstream>
#include "ReadCsv.h"


void ReadCsv::readStops(vector<Stop>& stops) {
    string content;
    string file = "../Dataset/stops.csv";
    ifstream myFile(file);
    getline(myFile, content);
    while (getline(myFile, content)) {
        stringstream stream(content);
        string code, name, zone, latitudeStr, longitudeStr;
        double latitude, longitude;
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, zone, ',');
        getline(stream, latitudeStr, ',');
        getline(stream, longitudeStr);
        stream.clear();
        stream.str(latitudeStr);
        stream >> latitude;
        stream.clear();
        stream.str(longitudeStr);
        stream >> longitude;

        Stop stop(code, name, zone, latitude, longitude);

        stops.push_back(stop);
    }
}

void ReadCsv::readLines(vector<Line> &lines, bool nightShift) {
    string content;
    string file = "../Dataset/lines.csv";
    ifstream myFile(file);
    while (getline(myFile, content)) {
        stringstream stream(content);
        string lineCode, name;
        getline(stream, lineCode, ',');
        getline(stream, name);
        if (lineCode[lineCode.size() - 1] == 'M' && !nightShift) continue;
        if (lineCode[lineCode.size() - 1] != 'M' && nightShift) continue;
        Line line(lineCode, name);
        lines.push_back(line);
    }
}

void ReadCsv::readLine(string code, string dir, vector<string>& codes) {
    string content;
    string file = "../Dataset/line_" + code + "_" + dir + ".csv";

    ifstream  myFile(file);
    getline(myFile, content);

    while (getline(myFile, content)) {
        codes.push_back(content);
    }
}
