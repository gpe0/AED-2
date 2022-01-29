#include "Interface.h"
#include <iostream>
#include <fstream>
#include "STCPManager.h"
#include "Map.h"
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
    Trip trip;
    if (choice == 0){
        string oCode, dCode;
        cout << "Paragem de origem: " << flush;
        cin >> oCode;
        cout << "Paragem de destino: " << flush;
        cin >> dCode;
        trip = manager->pathBetweenStops(oCode, dCode);
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
        trip = manager->pathBetweenStops(lat, lon, dCode);
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
        trip = manager->pathBetweenStops(oCode, lat, lon);
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
        trip = manager->pathBetweenStops(lat1, lon1, lat2, lon2);
    }
    string res;
    cout << "Exportar informacao da viagem [Y/N]: " << flush;
    cin >> res;
    if (res[0] == 'Y' || res[0] == 'y') exportData(trip, mode);

    printTripInfo(trip, mode);
}

void Interface::printTripInfo(Trip trip, int mode) {

    if (trip.getStopsPath().size() == 0) cout << "Sem caminho!" << endl;
    else {
        if (mode == 0) cout << "Numero de paragens: " << trip.getDistance() << endl;
        else cout << "Distancia total (Km): " << trip.getDistance() << endl;
        cout << "Zonas: " << trip.getDifZones() << endl;
        list<Line> lines = trip.getLinesPath();
        auto lineIt = lines.begin();

        for (auto ele: trip.getStopsPath()) {
            string line = "";
            if (lineIt != lines.end()) {
                line = " (" + lineIt->getCode() + ")";
                lineIt++;
            }
            cout << ele.getCode() << line << " -> " << flush;
        }
        cout << "chegada!" << endl;
    }
}

void Interface::exportData(Trip trip, int mode) {
    string generalInfo = "../Output/generalInfo.csv";
    string stopList = "../Output/stopList.csv";
    string lineList = "../Output/lineList.csv";
    string tripMap = "../Output/tripMap.html";

    Map map;

    ofstream f(generalInfo);
    if (f.is_open()) {
        f << "Primeira Paragem,Ultima Paragem,Distancia Total,Zonas,Numero de paragens" << endl;
        if(trip.getStopsPath().size() != 0) {
            f << trip.getStopsPath().front().getCode() << "," << trip.getStopsPath().back().getCode() << "," << flush;
            if (mode == 0) f << "---," << flush;
            else f << trip.getDistance() << "," << flush;
            f << trip.getDifZones() << "," << trip.getStopsPath().size() << endl;
        }
    }
    f.close();
    f.open(stopList);
    if (f.is_open()) {
        f << "Codigo da Paragem,Nome da Paragem,Zona,Latitude,Longitude" << endl;
        list<Stop> stops = trip.getStopsPath();
        for (auto it = stops.begin(); it != stops.end(); it++) {
            f << it->getCode() << "," << it->getName() << "," << it->getZone() << "," << it->getLatitude() << "," << it->getLongitude() << endl;
            map.addStop(*it);
            auto next = std::next(it, 1);
            if (next != stops.end()) map.addConnection(*it, *next);
        }

    }
    f.close();
    f.open(lineList);
    if (f.is_open()) {
        f << "Codigo da Linha,Nome da Linha" << endl;
        for (auto line : trip.getLinesPath())
            f << line.getCode() << "," << line.getName() << endl;
    }

    f.close();
    f.open(tripMap);
    if (f.is_open()) f << map.getHTML() << endl;
    f.close();
}