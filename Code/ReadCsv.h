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
    /**Reads every stop from the stops.csv file
     *
     * @param stops list of every stop
     */
    void readStops(vector<Stop>& stops);

    /**Reads every line from the lines.csv file from one of the shifts (day or night)
     *
     * @param lines list of every line
     * @param nightShift is it night shift
     */
    void readLines(vector<Line>& lines, bool nightShift);

    /**Reads the sequence of stops for a particular line
     *
     * @param code line code
     * @param dir line direction
     * @param codes list of codes of every stop
     */
    void readLine(string code, string dir, vector<string>& codes);
};


#endif
