//
// Created by Маргарита Гусарова on 14.05.2023.
//

#include "Graph.h"

Graph::~Graph() {
    for (auto & i : graph) {
        Edge *edge = i.edge;
        while (edge != nullptr) {
            Edge *tmp = edge;
            edge = edge->next;
            delete tmp;
        }
    }
}

int Graph::find_vertex(int id) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].id == id) {
            return i;
        }
    }
    return -1;
}




