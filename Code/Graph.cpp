#include "Graph.h"
#include <climits>

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight});
    if (!hasDir) nodes[dest].adj.push_back({src, weight});
}

int Graph::dijkstra_distance(int a, int b) {

    MinHeap<int, int> minHeap(nodes.size(), -1);

    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].dist = INT_MAX;
        nodes[i].visited = false;
        minHeap.insert(i, nodes[i].dist);
    }
    nodes[a].dist = 0;
    minHeap.decreaseKey(a, 0);
    while (minHeap.getSize() != 0) {
        int u = minHeap.removeMin();
        if (!nodes[u].visited) {
            nodes[u].visited = true;
            for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {
                if (!nodes[(*it).dest].visited && nodes[(*it).dest].dist > nodes[u].dist + (*it).weight) {
                    nodes[(*it).dest].dist = nodes[u].dist + (*it).weight;
                    minHeap.decreaseKey((*it).dest, nodes[u].dist + (*it).weight);
                }
            }
        }

    }
    if (nodes[b].dist == INT_MAX) return -1;
    return nodes[b].dist;
}

list<int> Graph::dijkstra_path(int a, int b) {
    list<int> path;

    MinHeap<int, int> minHeap(nodes.size(), -1);

    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].dist = INT_MAX;
        nodes[i].visited = false;
        nodes[i].pred = 0;
        minHeap.insert(i, nodes[i].dist);
    }
    nodes[a].dist = 0;
    nodes[a].pred = a;
    minHeap.decreaseKey(a, 0);
    while (minHeap.getSize() != 0) {
        int u = minHeap.removeMin();
        if (!nodes[u].visited) {
            nodes[u].visited = true;
            for (auto it = nodes[u].adj.begin(); it != nodes[u].adj.end(); it++) {
                if (!nodes[(*it).dest].visited && nodes[(*it).dest].dist > nodes[u].dist + (*it).weight) {
                    nodes[(*it).dest].dist = nodes[u].dist + (*it).weight;
                    nodes[(*it).dest].pred = u;
                    minHeap.decreaseKey((*it).dest, nodes[u].dist + (*it).weight);
                }
            }
        }

    }
    int i = b;

    if (nodes[b].dist == INT_MAX) return path;

    while (i != a) {
        path.push_front(i);
        i = nodes[i].pred;
    }

    path.push_front(a);

    return path;
}
