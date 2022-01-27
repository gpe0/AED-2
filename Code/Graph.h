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
        std::string originZone, destinationZone;
    };

    struct Node {
        std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        double dist;
        double backDist;
        int pred;
        Line predLine;
        int difZones;
        bool visited;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    std::vector<Node> nodes; // The list of nodes being represented

    /**Dijkstra’s Algorithm (n*log(n))
     *
     * @param s source node
     * @param choice user's choice
     * @param w initial weight (default is zero)
     */
    void dijkstra(int s, int choice, double w = 0);

    /**Breadth-First Search (n^2)
     *
     * @param i source node
     */
    void bfs(int i);

public:
    /**Graph's constructor given the total number of nodes and a direction (default: undirected)
     *
     * @param nodes total number of nodes
     * @param dir direction
     */
    Graph(int nodes, bool dir = false);

    /**Adds an edge from source to destination with a certain weight
     *
     * @param src origin node
     * @param dest destination node
     * @param line connection line
     * @param originZone origin zone
     * @param destinationZone destination node
     * @param weight line weight (might be distance or just an indicator of a line (for BFS))
     */
    void addEdge(int src, int dest, Line line, std::string originZone, std::string destinationZone, double weight = 1);

    /**Returns the number of stops it takes to get from a node to another using BFS
     *
     * @param a origin node
     * @param b destination node
     * @return number of stops
     */
    double bfs_distance(int a, int b);

    /**Returns the path beetween to stops using BFS
     *
     * @param a origin node
     * @param b destination node
     * @param currentLine line path
     * @param difZones number of different zones
     * @return path beetween to stops
     */
    std::list<int> bfs_path(int a, int b, list<Line>& currentLine, int & difZones);

    /**Returns the number of stops it takes to get from a node to another using Dijkstra
     *
     * @param a origin node
     * @param b destination node
     * @param currentLine line path
     * @param choice user's choice
     * @param w initial distance
     * @return number of stops
     */
    double dijkstra_distance(int a, int b, list<Line>& currentLine, int choice, double w = 0);

    /**Returns the path beetween to stops using Dijkstra
     *
     * @param a origin node
     * @param b destination node
     * @param currentLine line path
     * @param difZones number of different zones
     * @param choice user's choice
     * @param w initial distance
     * @return path beetween to stops
     */
    std::list<int> dijkstra_path(int a, int b, list<Line>& currentLine, int & difZones, int choice, double  w = 0);
};


#endif
