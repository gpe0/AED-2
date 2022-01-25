#ifndef AED_2_INTERFACE_H
#define AED_2_INTERFACE_H

#include "STCPManager.h"


class Interface {
    static void drawMenu();
    static void drawChoices();
    static void simulateTrip(STCPManager* manager, int mode);
    static void printTripInfo(Trip trip, int mode);
public:
    static void menu();
};


#endif
