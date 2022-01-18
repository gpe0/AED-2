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

public:
    void readStops(string file);
    void getStops();
};


#endif
