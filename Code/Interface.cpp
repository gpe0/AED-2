#include "Interface.h"
#include <iostream>
#include "STCPManager.h"
using namespace std;

void Interface::drawMenu() {
    cout << "-------------------------" << endl;
    cout << "Simulador de viagens STCP" << endl;
    cout << "-------------------------" << endl << endl;
}

void Interface::drawChoices() {
    cout << "Como pretende viajar? " << endl;
    cout << "0 - Menos paragens" << endl;
    cout << "1 - Menor distancia" << endl;
    cout << "2 - Trocar o menos possivel de linha" << endl;
    cout << "3 - Mais barato" << endl;
    cout << "4 - Mais barato (trocando o menos possivel de linha)" << endl;
    cout << "5 - Nao pretende viajar" << endl << endl;
    cout << "Opcao: " << flush;
}

void Interface::menu() {
    while (true) {
        drawMenu();
        drawChoices();
        int choice;
        double walkableToFromStops, walkableBeetweenStops;
        bool nightShift;
        string res;
        cin >> choice;
        while (choice < 0 || choice > 5) {
            cout << "Erro de input, tente novamente." << endl;
            cout << "Opcao: " << flush;
            cin >> choice;
        }

        if (choice == 5) break;
        cout
                << "Quantos metros esta disposto a andar (do local onde esta ate a paragem e da paragem ao local de destino): "
                << flush;
        cin >> walkableToFromStops;
        walkableToFromStops /= 1000;

        cout << "Quantos metros esta disposto a andar entre paragens : " << flush;
        cin >> walkableBeetweenStops;
        walkableBeetweenStops /= 1000;

        cout << "Vai viajar de madrugada (rede noturna) [Y/N]: " << flush;
        cin >> res;
        if (res[0] == 'Y' || res[0] == 'y') nightShift = true;
        else nightShift = false;

        cout << "A Gerar rede..." << endl;
        STCPManager manager(choice, walkableBeetweenStops, walkableToFromStops, nightShift);
        manager.generateGraph();

        cout << "Rede Gerada!" << endl << endl;

        simulateTrip(&manager, choice);
    }
}

void Interface::simulateTrip(STCPManager* manager, int mode) {
    int choice;
    cout << "Dados fornecidos: " << endl;
    cout << "0 - Duas paragens" << endl;
    cout << "1 - Localizacao de origem e paragem de destino" << endl;
    cout << "2 - Paragem de origem e localizacao de destino" << endl;
    cout << "3 - Duas localizacoes" << endl << endl;
    cout << "Opcao: " << flush;
    cin >> choice;
    while (choice < 0 || choice > 3) {
        cout << "Erro de input, tente novamente." << endl;
        cout << "Opcao: " << flush;
        cin >> choice;
    }
    if (choice == 0){
        string oCode, dCode;
        cout << "Paragem de origem: " << flush;
        cin >> oCode;
        cout << "Paragem de destino: " << flush;
        cin >> dCode;
        Trip trip = manager->pathBeetweenStops(oCode, dCode);
        printTripInfo(trip, mode);
    }
    else if (choice == 1) {
        double lat, lon;
        string dCode;
        cout << "Latitude de origem: " << flush;
        cin >> lat;
        cout << "Longitude de origem: " << flush;
        cin >> lon;
        cout << "Paragem de destino: " << flush;
        cin >> dCode;
        Trip trip = manager->pathBeetweenStops(lat, lon, dCode);
        printTripInfo(trip, mode);
    }
    else if (choice == 2) {
        double lat, lon;
        string oCode;
        cout << "Paragem de origem: " << flush;
        cin >> oCode;
        cout << "Latitude de destino: " << flush;
        cin >> lat;
        cout << "Longitude de destino: " << flush;
        cin >> lon;
        Trip trip = manager->pathBeetweenStops(oCode, lat, lon);
        printTripInfo(trip, mode);
    }
    else {
        double lat1, lon1, lat2, lon2;
        cout << "Latitude de origem: " << flush;
        cin >> lat1;
        cout << "Longitude de origem: " << flush;
        cin >> lon1;
        cout << "Latitude de destino: " << flush;
        cin >> lat2;
        cout << "Longitude de destino: " << flush;
        cin >> lon2;
        Trip trip = manager->pathBeetweenStops(lat1, lon1, lat2, lon2);
        printTripInfo(trip, mode);
    }
}

void Interface::printTripInfo(Trip trip, int mode) {
    if (mode == 0) cout << "Numero de paragens: " << trip.getDistance() << endl;
    else cout << "Distancia total (Km): " << trip.getDistance() << endl;
    cout << "Zonas: " << trip.getDifZones() << endl;
    list<Line> lines = trip.getLinesPath();
    auto lineIt = lines.begin();


    for (auto ele : trip.getStopsPath()) {
        string line = "";
        if (lineIt != lines.end()) {
            line = " (" + lineIt->getCode() + ")";
            lineIt++;
        }
        cout << ele << line << " -> "<< flush;
    }
    cout << "chegada!" << endl;
}