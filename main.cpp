#include <iostream>
#include "Graph.h"
static vector<Vertex> visited;
using namespace std;


int main() {
    std::function<vector<Vertex>(const Vertex& )> action;

    Graph graph;
    action = [](const Vertex& vertex){
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
    vector<Vertex> walk_path = visited;
    vector<int> path = graph.shortest_path(10, 60)[0];
    cout << endl;
    vector<int> distance_all =  graph.shortest_path(10, 60)[1];
    cout << "Длина кратчайшего пути: " << distance_all[5] << endl;
    cout << "Кратчайший путь: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl << "Кратчайшие пути до всех вершин:" << endl;
    for (int i = 0; i < distance_all.size(); i++) {
        cout << distance_all[i] << " ";
    }
    vector<int > V = graph.max_average_length();
    cout << endl;
    cout << "Вершина с максимальным весом ребер: " << V[0] << endl;
    cout << "Вес ребер: " << V[1] << endl;


    return 0;


}
