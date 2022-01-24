#include <string>
#include <cmath>
#include "STCPManager.h"

#define INF (INT_MAX/2)

using namespace std;

STCPManager::STCPManager(int choice, double walkableBeetweenStops, double walkableToFromStops) {
    this->choice = choice;
    this->walkableBeetweenStops = walkableBeetweenStops;
    this->walkableToFromStops = walkableToFromStops;
    reader.readStops(stopList);
    reader.readLines(lineList, false);
    this->stops = new Graph(stopList.size(), true);

    int num = 1;
    for (Stop stop : stopList) {
        codeToInt[stop.getCode()] = num;
        num++;
    }
}

double STCPManager::distanceBeetweenTwoPoints(double lat1, double lon1, double lat2, double lon2) {
    double earthR = 6371;
    double difLat = (lat2 - lat1) * M_PI / 180;
    double difLon = (lon2 - lon1) * M_PI / 180;

    lat1 = lat1 * M_PI  / 180;
    lat2 = lat2 * M_PI  / 180;

    double a = pow(sin(difLat / 2), 2) + pow(sin(difLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));

    return earthR * c;
}

void STCPManager::setChoice(int choice) {
    this->choice = choice;
}

void STCPManager::setWalkableBeetweenStops(double walkableBeetweenStops) {
    this->walkableBeetweenStops = walkableBeetweenStops;
}

void STCPManager::setWalkableToFromStops(double walkableToFromStops) {
    this->walkableToFromStops = walkableToFromStops;
}

void STCPManager::clearGraph() {
    delete stops;
    this->stops = new Graph(stopList.size(), true);
}

void STCPManager::generateGraph() {


    for (Line line : lineList) {
        vector<string> codes;

        reader.readLine(line.getCode(), "0", codes);

        for (int i = 1; i < codes.size(); i++) {
            double weight = distanceBeetweenTwoPoints(stopList[codeToInt[codes[i - 1]] - 1].getLatitude(), stopList[codeToInt[codes[i - 1]] - 1].getLongitude(), stopList[codeToInt[codes[i]] - 1].getLatitude(), stopList[codeToInt[codes[i]] - 1].getLongitude());
            stops->addEdge(codeToInt[codes[i - 1]], codeToInt[codes[i]], line, weight);
        }
        codes.clear();

        reader.readLine(line.getCode(), "1", codes);
        for (int i = 1; i < codes.size(); i++) {
            double weight = distanceBeetweenTwoPoints(stopList[codeToInt[codes[i - 1]] - 1].getLatitude(), stopList[codeToInt[codes[i - 1]] - 1].getLongitude(), stopList[codeToInt[codes[i]] - 1].getLatitude(), stopList[codeToInt[codes[i]] - 1].getLongitude());
            stops->addEdge(codeToInt[codes[i - 1]], codeToInt[codes[i]], line, weight);
        }
    }
    if (choice < 3) return;

    Line l("WALK", "Just Walking");
    for (Stop stop1: stopList) {
        for (Stop stop2: stopList) {
            double dist = distanceBeetweenTwoPoints(stop1.getLatitude(), stop1.getLongitude(), stop2.getLatitude(), stop2.getLongitude());
            if (dist <= walkableBeetweenStops) stops->addEdge(codeToInt[stop1.getCode()], codeToInt[stop2.getCode()], l, dist);
        }
    }
}

Trip STCPManager::pathBeetweenStops(string a, string b) {
    list<string> stopsPath;
    list<Line> linesPath;
    list<int> aux = stops->dijkstra_path(codeToInt[a], codeToInt[b], linesPath, choice);
    double distance = stops->dijkstra_distance(codeToInt[a], codeToInt[b], linesPath, choice);

    for (const auto & element : aux) {
        stopsPath.push_back(stopList[element - 1].getCode() );
    }

    Trip trip(stopsPath, linesPath, distance);

    return trip;
}

Trip STCPManager::pathBeetweenStops(double lat1, double lon1, string b) {
    list<string> stopsPath;
    list<Line> linesPath;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop : stopList) {
        double distance = distanceBeetweenTwoPoints(lat1, lon1, stop.getLatitude(), stop.getLongitude());
        if (distance >= walkableToFromStops) continue;
        linesPath.clear();
        list<int> newPath = stops->dijkstra_path(codeToInt[stop.getCode()], codeToInt[b],linesPath, choice, distance);
        double newDistance = stops->dijkstra_distance(codeToInt[stop.getCode()], codeToInt[b], linesPath, choice, distance);
        if (newDistance < bestDistance && !newPath.empty()) {
            bestDistance = newDistance;
            max = newPath;
            bestLine = linesPath;
        }
    }

    for (const auto & element : max) {
        stopsPath.push_back(stopList[element - 1].getCode());
    }

    Trip trip(stopsPath, bestLine, bestDistance);

    return trip;
}

Trip STCPManager::pathBeetweenStops(double lat1, double lon1, double lat2, double lon2) {
    list<string> stopsPath;
    list<Line> linesPath;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop1 : stopList) {
        double distance1 = distanceBeetweenTwoPoints(lat2, lon2, stop1.getLatitude(), stop1.getLongitude());
        if (distance1 >= walkableToFromStops) continue;
        for (Stop stop2: stopList) {
            double distance2 = distanceBeetweenTwoPoints(lat1, lon1, stop2.getLatitude(), stop2.getLongitude());
            if (distance2 >= walkableToFromStops) continue;
            linesPath.clear();
            list<int> newPath = stops->dijkstra_path(codeToInt[stop2.getCode()], codeToInt[stop1.getCode()], linesPath, choice, distance2);
            double newDistance = stops->dijkstra_distance(codeToInt[stop2.getCode()], codeToInt[stop1.getCode()], linesPath, choice ,distance2) + distance1;
            if (newDistance < bestDistance && newDistance > 0 && !newPath.empty()) {
                bestDistance = newDistance;
                max = newPath;
                bestLine = linesPath;
            }
        }
    }

    for (const auto & element : max) {
        stopsPath.push_back(stopList[element - 1].getCode());
    }

    Trip trip(stopsPath, bestLine, bestDistance);

    return trip;

}

Trip STCPManager::pathBeetweenStops(string a, double lat2, double lon2) {
    list<string> stopsPath;
    list<Line> linesPath;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop : stopList) {
        double distance = distanceBeetweenTwoPoints(lat2, lon2, stop.getLatitude(), stop.getLongitude());
        if (distance >= walkableToFromStops) continue;
        linesPath.clear();
        list<int> newPath = stops->dijkstra_path(codeToInt[a], codeToInt[stop.getCode()], linesPath, choice);

        double newDistance = stops->dijkstra_distance(codeToInt[a], codeToInt[stop.getCode()], linesPath, choice) + distance;
        if (newDistance < bestDistance && !newPath.empty()) {
            bestDistance = newDistance;
            max = newPath;
            bestLine = linesPath;
        }
    }
    for (const auto & element : max) {
        stopsPath.push_back(stopList[element - 1].getCode());
    }

    Trip trip(stopsPath, bestLine, bestDistance);

    return trip;
}

STCPManager::~STCPManager() {
    delete stops;
}
