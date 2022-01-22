#ifndef AED_2_LINE_H
#define AED_2_LINE_H

#include <string>

class Line {
    std::string code, name;

public:
    Line();
    Line(std::string code, std::string name);

    std::string getCode();
    std::string getName();
};


#endif
