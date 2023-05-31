//
// Created by ��࣠�� ���஢� on 14.05.2023.
//

#include "Graph.h"
#include <iostream>
#include <vector>
using namespace std;

Graph::~Graph() {
    for (auto & i : graph) {
        vector <Edge> edge = i.edge;
        while (edge.begin() != edge.end()) {
            delete_edge(i.id, edge.begin()->id);
        }
        delete_vertex(i.id);
    }
    graph.clear();
}

int Graph::find_vertex(int id) const {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].id == id) {
            return i;
        }
    }
    return -1;
}

bool Graph::add_vertex(int id) {
    if (find_vertex(id) != -1) {
        return false;
    }
    Vertex vertex(id);
    graph.push_back(vertex);
    return true;
}

bool Graph::delete_vertex(int id) {
    int index = find_vertex(id);
    if (index == -1) {
        return false;
    }
    vector<Edge> edge = graph[index].edge;
    while (edge.begin() != edge.end()) {
        delete_edge(id, edge.begin()->id);
        edge.begin()++;
    }

    graph.erase(graph.begin() + index);
    return true;
}

bool Graph::find_edge(int id_from, int id_to) {
    int index_from = find_vertex(id_from);
    if (index_from == -1) {
        return false;
    }
    vector<Edge> edge = graph[index_from].edge;
    if (edge.size()==1 && edge.begin()->id == id_to) {
        return true;
    }
    if (edge.size()==1 && edge.begin()->id != id_to){
        return false;}

    while (edge.begin() != edge.end()) {
        if (edge.begin()->id == id_to) {
            return true;
        }
        edge.begin()++;
    }
    return false;
}

bool Graph::add_edge(int id_from, int id_to, int weight) {
    int index_from = find_vertex(id_from);
    int index_to = find_vertex(id_to);
    if (index_from == -1 || index_to == -1) {
        return false;
    }
    if (find_edge(id_from, id_to)) {
        return false;
    }
    graph[index_from].edge.emplace_back(id_to, weight); // � �ࠧ� ��।��� ���������
    return true;
}

bool Graph::delete_edge(int id_from, int id_to) {
    int index_from = find_vertex(id_from);
    if (index_from == -1) {
        return false;
    }
    vector <Edge> edge= graph[index_from].edge;
    if (edge.begin()->id == id_to) {
        graph[index_from].edge.erase(edge.begin());
        return true;
    }
    while (edge.begin() != edge.end()) {
        if (edge.begin()->id == id_to) {
            graph[index_from].edge.erase(edge.begin());
            return true;
        }
        edge.begin()++;
    }
}

vector<Edge>& Graph::edges(const Vertex &vertex) {
    int index = find_vertex(vertex.id);
    if (index == -1) {
        throw "Vertex not found";
    }
    return graph[index].edge;
}

size_t Graph::order() const {
    return graph.size();
}

size_t Graph::degree() const {
    int max = 0;
    for (auto & i : graph) {
        if (i.edge.size() > max) {
            max = i.edge.size();
        }
    }
    return max;
}

void Graph::print() const {
    for (auto & i : graph) {
        cout << i.id << ": ";
        vector <Edge> edge = i.edge;
        while (edge.begin() != edge.end()) {
            cout << edge.begin()->id << " ";
            edge.begin()++;
        }
        cout << endl;
    }
}



bool vector_contains(const vector<Vertex> &v, const Vertex &vertex) {
    for (auto & i : v) {
        if (i.id == vertex.id) {
            return true;
        }
    }
    return false;
}

vector<Vertex> Graph::walk_bfs(int index_v, const function<vector<Vertex>(const Vertex &)>& action) const {
    Vertex start_vertex = graph[index_v];
    vector<Vertex> walk_v;
    vector<Vertex> queue;
    queue.push_back(start_vertex);
    while (!queue.empty()) {
        Vertex v = queue[0];
        walk_v.push_back(v);
        queue.erase(queue.begin());
        action(v);
        vector<Edge> edges = v.edge;
        int i = 0;

        while (i < edges.size()) {


            int index = find_vertex(edges[i].id);
            if (!vector_contains(walk_v, graph[index])) {
                queue.push_back(graph[index]);
            }

            i++;
        }
    }
    return walk_v;
}

vector<Edge> Graph::shortest_path(const Vertex &from, const Vertex &to) const {

}












