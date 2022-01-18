#ifndef AED_2_READCSV_H
#define AED_2_READCSV_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class ReadCsv {
private:
    string file;
    string code, name, zone, latitude, longitude;
    vector<string> stops;
    vector<string> line;

public:
    void readStops(string file);
    void readLine(string code, string dir);
    void getStops();
    void getLine();
};


#endif
