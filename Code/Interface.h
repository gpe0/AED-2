#ifndef AED_2_INTERFACE_H
#define AED_2_INTERFACE_H

#include "STCPManager.h"


class Interface {
    /**Displays a simple menu
     *
     */
    static void drawMenu();
    /**Displays a user's choices
     *
     */
    static void drawChoices();
    /**Simulates a trip
     *
     * @param manager STCP manager
     * @param mode user's choice
     */
    static void simulateTrip(STCPManager* manager, int mode);
    /**Shows in the terminal everything about the trip for a specific mode
     *
     * @param trip Trip
     * @param mode user's choice
     */
    static void printTripInfo(Trip trip, int mode);

    /**Exports the information about a trip to files (csv and html)
     *
     * @param trip trip
     */
    static void exportData(Trip trip, int mode);
public:
    /**Runs the menu loop
     *
     */
    static void menu();
};


#endif
