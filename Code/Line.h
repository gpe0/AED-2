#ifndef AED_2_LINE_H
#define AED_2_LINE_H

#include <string>

class Line {
    std::string code, name;

public:
    /**Instantiates a line with no code and no name
     *
     */
    Line();

    /**Instantiates a line given a code and a name
     *
     * @param code code
     * @param name name
     */
    Line(std::string code, std::string name);

    /**Returns line's code
     *
     * @return code
     */
    std::string getCode();

    /**Returns line's name
     *
     * @return name
     */
    std::string getName();
};


#endif
