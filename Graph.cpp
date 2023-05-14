//
// Created by Маргарита Гусарова on 14.05.2023.
//

#include "Graph.h"

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

int Graph::find_vertex(int id) {
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
    graph[index_from].edge.emplace_back(id_to, weight); // тк сразу передаем конструктор
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



