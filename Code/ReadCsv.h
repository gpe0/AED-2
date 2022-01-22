#ifndef AED_2_READCSV_H
#define AED_2_READCSV_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Stop.h"
#include "Line.h"

using namespace std;

class ReadCsv {
public:
    void readStops(vector<Stop>& stops);
    void readLines(vector<Line>& lines, bool nightShift);
    void readLine(string code, string dir, vector<string>& codes);
};


#endif
