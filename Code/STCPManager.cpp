#include <string>
#include <cmath>
#include "STCPManager.h"

#define INF (INT_MAX/2)

using namespace std;

STCPManager::STCPManager() {
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
}

list<string> STCPManager::pathBeetweenStops(string a, string b) {
    list<string> res;
    list<Line> lines;
    list<int> aux = stops->dijkstra_path(codeToInt[a], codeToInt[b], lines);
    auto lineIt = lines.begin();
    for (auto pathIt = aux.begin(); pathIt != aux.end(); pathIt++) {
        string currentLine;
        if (pathIt != aux.begin()) {
            currentLine = "(" + lineIt->getCode() + ") ";
            lineIt++;
        }
        res.push_back(currentLine + stopList[*pathIt - 1].getCode() );
    }

    return res;
}

list<string> STCPManager::pathBeetweenStops(double lat1, double lon1, string b) {
    list<string> res;
    list<Line> lines;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop : stopList) {
        double distance = distanceBeetweenTwoPoints(lat1, lon1, stop.getLatitude(), stop.getLongitude());
        if (distance >= 0.5) continue;
        double newDistance = stops->dijkstra_distance(codeToInt[stop.getCode()], codeToInt[b], distance);
        lines.clear();
        list<int> newPath = stops->dijkstra_path(codeToInt[stop.getCode()], codeToInt[b],lines, distance);
        if (newDistance < bestDistance && !newPath.empty()) {
            bestDistance = newDistance;
            max = newPath;
            bestLine = lines;
        }
    }
    auto lineIt = bestLine.begin();
    for (auto pathIt = max.begin(); pathIt != max.end(); pathIt++) {
        string currentLine;
        if (pathIt != max.begin()) {
            currentLine = "(" + lineIt->getCode() + ") ";
            lineIt++;
        }

        res.push_back(currentLine + stopList[*pathIt - 1].getCode() );
    }

    return res;
}

list<string> STCPManager::pathBeetweenStops(double lat1, double lon1, double lat2, double lon2) {
    list<string> res;
    list<Line> lines;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop1 : stopList) {
        double distance1 = distanceBeetweenTwoPoints(lat2, lon2, stop1.getLatitude(), stop1.getLongitude());
        if (distance1 >= 0.5) continue;
        for (Stop stop2: stopList) {
            double distance2 = distanceBeetweenTwoPoints(lat1, lon1, stop2.getLatitude(), stop2.getLongitude());
            if (distance2 >= 0.5) continue;
            double newDistance = stops->dijkstra_distance(codeToInt[stop2.getCode()], codeToInt[stop1.getCode()], distance2) + distance1;
            lines.clear();
            list<int> newPath = stops->dijkstra_path(codeToInt[stop2.getCode()], codeToInt[stop1.getCode()], lines, distance2);
            if (newDistance < bestDistance && !newPath.empty()) {
                bestDistance = newDistance;
                max = newPath;
                bestLine = lines;
            }
        }
    }

    auto lineIt = bestLine.begin();
    for (auto pathIt = max.begin(); pathIt != max.end(); pathIt++) {
        string currentLine;
        if (pathIt != max.begin()) {
            currentLine = "(" + lineIt->getCode() + ") ";
            lineIt++;
        }

        res.push_back(currentLine + stopList[*pathIt - 1].getCode() );
    }

    return res;

}

list<string> STCPManager::pathBeetweenStops(string a, double lat2, double lon2) {
    list<string> res;
    list<Line> lines;
    list<Line> bestLine;
    list<int> max;
    double bestDistance = INF;
    for (Stop stop : stopList) {
        double distance = distanceBeetweenTwoPoints(lat2, lon2, stop.getLatitude(), stop.getLongitude());
        if (distance >= 0.5) continue;
        double newDistance = stops->dijkstra_distance(codeToInt[a], codeToInt[stop.getCode()]) + distance;
        lines.clear();
        list<int> newPath = stops->dijkstra_path(codeToInt[a], codeToInt[stop.getCode()], lines);
        if (newDistance < bestDistance && !newPath.empty()) {
            bestDistance = newDistance;
            max = newPath;
            bestLine = lines;
        }
    }
    auto lineIt = bestLine.begin();
    for (auto pathIt = max.begin(); pathIt != max.end(); pathIt++) {
        string currentLine;
        if (pathIt != max.begin()) {
            currentLine = "(" + lineIt->getCode() + ") ";
            lineIt++;
        }

        res.push_back(currentLine + stopList[*pathIt - 1].getCode() );
    }

    return res;
}

STCPManager::~STCPManager() {
    delete stops;
}
