#include <iostream>
#include "Code/ReadCsv.h"

using namespace std;

int main() {
    cout << "AED 2021/2022 - Projeto 2" << endl;
    ReadCsv reader;
    reader.readLine("505", "0");
    reader.getLine();
    return 0;
}
