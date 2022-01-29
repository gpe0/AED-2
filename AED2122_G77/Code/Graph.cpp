#include "Graph.h"
#include <climits>
#include <queue>

#define INF (INT_MAX/2)

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, Line line, std::string originZone, std::string destinationZone, double weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line, originZone, destinationZone});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line, originZone, destinationZone});
}

void Graph::dijkstra(int s, int choice, double w) {
    MinHeap<int, int> minHeap(n, -1);
    for (int i = 1; i <= n; i++) {
        nodes[i].dist = INF;
        nodes[i].backDist = INF;
        nodes[i].visited = false;
        minHeap.insert(i, INF);
    }
    nodes[s].backDist = w;
    nodes[s].dist = w;
    nodes[s].pred = s;
    nodes[s].difZones = 1;
    minHeap.decreaseKey(s,0);

    while (minHeap.getSize() > 0) {
        int u = minHeap.removeMin();
        nodes[u].visited = true;
        for (const auto & edge : nodes[u].adj) {
            int v = edge.dest;
            double w = edge.weight;
            if (!nodes[v].visited && nodes[u].backDist + w < nodes[v].backDist) {
                nodes[v].predLine = edge.line;
                if ((choice == 2 || choice == 4) && nodes[v].predLine.getCode() != nodes[u].predLine.getCode()){
                    nodes[v].backDist = nodes[u].backDist + w + 50;
                }
                else nodes[v].backDist = nodes[u].backDist + w;

                if (edge.originZone != edge.destinationZone) {
                    if ((choice == 3 || choice == 4)) nodes[v].backDist = nodes[u].backDist + w + 50;
                    nodes[v].difZones = nodes[u].difZones + 1;
                } else nodes[v].difZones = nodes[u].difZones;


                nodes[v].dist = nodes[u].dist + w;

                minHeap.decreaseKey(v, nodes[v].backDist);
                nodes[v].pred = u;
            }
        }

    }
}

void Graph::bfs(int v) {
    for (int v = 1; v <= n; v++) nodes[v]. visited = false;
    queue<int> q;
    q.push(v);
    nodes[v].dist = 1;
    nodes[v].visited = true;
    nodes[v].pred = v;
    nodes[v].difZones = 1;
    while (!q.empty ()) {
        int u = q.front (); q.pop ();
        for (auto e : nodes[u]. adj) {
            int w = e.dest;
            if (! nodes[w]. visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                nodes[w].pred = u;
                nodes[w].predLine = e.line;
                if (e.originZone != e.destinationZone) nodes[w].difZones = nodes[u].difZones + 1;
                else nodes[w].difZones = nodes[u].difZones;
            }
        }
    }
}


double Graph::dijkstra_distance(int a, int b, list<Line>& currentLine, int choice, double w) {
    dijkstra(a, choice ,w);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

list<int> Graph::dijkstra_path(int a, int b, list<Line>& currentLine, int & difZones, int choice, double w) {
    dijkstra(a, choice , w);
    list<int> path;

    if (nodes[b].dist == INF) return path;
    difZones = nodes[b].difZones;
    path.push_back(b);
    currentLine.push_back(nodes[b].predLine);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
        if (v != a) currentLine.push_front(nodes[v].predLine);
    }
    return path;
}

double Graph::bfs_distance(int a, int b) {
    bfs(a);
    if (a != b && !nodes[b].visited) return -1;
    return nodes[b].dist;
}

std::list<int> Graph::bfs_path(int a, int b, list<Line> &currentLine, int & difZones) {
    bfs(a);
    list<int> path;
    if (a != b && !nodes[b].visited) return path;
    path.push_back(b);
    currentLine.push_back(nodes[b].predLine);
    difZones = nodes[b].difZones;
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
        if (v != a) currentLine.push_front(nodes[v].predLine);
    }
    return path;
}
