#include <iostream>
#include "Code/ReadCsv.h"

using namespace std;

int main() {
    cout << "AED 2021/2022 - Projeto 2" << endl;
    ReadCsv reader;
    reader.readStops("../Dataset/stops.csv");
    reader.getStops();
    return 0;
}
