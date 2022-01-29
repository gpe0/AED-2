#include "Line.h"

Line::Line() {
    this->code = "";
    this->name = "";
}

Line::Line(std::string code, std::string name) {
    this->code = code;
    this->name = name;
}

std::string Line::getCode() {
    return code;
}

std::string Line::getName() {
    return name;
}