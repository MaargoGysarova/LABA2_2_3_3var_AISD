#include <iostream>
#include "Graph.h"
using namespace std;


int main() {
    std::function<vector<Vertex>(const Vertex& )> action;

    Graph graph;
    action = [](const Vertex& vertex){
        vector<Vertex> visited;
        cout << vertex.id << endl;
        visited.push_back(vertex);
        return visited;
    };

    graph.add_vertex(10);
    graph.add_vertex(20);
    graph.add_vertex(30);
    graph.add_vertex(40);
    graph.add_vertex(50);
    graph.add_vertex(60);
    graph.add_edge(10, 20, 1);
    graph.add_edge(10, 30, 1);
    graph.add_edge(30, 60, 1);
    graph.add_edge(20, 40, 1);
    graph.add_edge(20, 50, 1);

    graph.walk_bfs(graph.find_vertex(10), action);

    return 0;


}
