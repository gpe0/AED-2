#ifndef AED_2_GRAPH_H
#define AED_2_GRAPH_H

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include "MinHeap.h"
#include "Line.h"

class Graph {

    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        Line line;
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double dist;
        int pred;
        Line predLine;
        bool visited;
        std::string code, name, zone;
        double latitude, longitude;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

    void dijkstra(int s, double w = 0);


public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, Line line, double weight = 1);


    // Shortest paths finder
    double dijkstra_distance(int a, int b, double w = 0);
    std::list<int> dijkstra_path(int a, int b, list<Line>& currentLine, double  w = 0);
};


#endif
