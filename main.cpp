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
    graph.add_vertex(70);
    graph.add_edge(10, 20, 3);
    graph.add_edge(10, 30, 3);
    graph.add_edge(30, 60, 4);
    graph.add_edge(60, 30, 4);
    graph.add_edge(20, 40, 3);
    graph.add_edge(20, 50, 2);
    graph.add_edge(50, 70, 12);
    graph.add_edge(50, 60, 5);
    graph.add_edge(60, 70, 10);


    graph.walk_bfs(graph.find_vertex(10), action);
    vector<int> path = graph.shortest_path(10, 60);
    //for (int i : path) {
     // cout << i;
    //}
    vector<int > V = graph.max_average_length();
    for (int i : V) {
        cout << i << endl;
    }


    return 0;


}
