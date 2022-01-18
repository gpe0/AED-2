#ifndef AED_2_GRAPH_H
#define AED_2_GRAPH_H

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include "MinHeap.h"

class Graph {

    struct Edge {
        int dest;   // Destination node
        int weight; // An integer weight
        std::string line;
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        std::string name;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented


public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int weight = 1);

    // Shortest paths finder
    int dijkstra_distance(int a, int b);
    std::list<int> dijkstra_path(int a, int b);
};


#endif
