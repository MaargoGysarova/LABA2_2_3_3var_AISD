
#include "Graph.h"
#include <iostream>
#include <vector>
#include <iterator>
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
        throw invalid_argument("Vertex already exists");
        return false;
    }
    Vertex vertex(id);
    graph.push_back(vertex);
    return true;
}

bool Graph::delete_vertex(int id) {
    int index = find_vertex(id);
    if (index == -1) {
        throw invalid_argument("Vertex already exists");
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
        throw invalid_argument("Vertex already exists");
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
        for(int j=0; j< edge.size(); j++) {
            cout << edge[j].id << "("<<edge[j].weight<<")" <<" ";
        }
        cout << endl;
    }
}


// функция проверки Узла в массиве
bool vector_contains(const vector<Vertex> &v, const Vertex &vertex) {
    for (auto & i : v) {
        if (i.id == vertex.id) {
            return true;
        }
    }
    return false;
}

// функция проверки наличия числа в векторе
bool vector_contains_2(const vector<int> &v, int number) {
    for (auto & i : v) {
        if (i == number) {
            return true;
        }
    }
    return false;
}

// Обход в ширину с испльзованием очереди
void Graph::walk_bfs(int index_v, const function<vector<Vertex>(const Vertex &)>& action) const {
    Vertex start_vertex = graph[index_v];
    vector<Vertex> walk_v;
    vector<Vertex> queue;
    queue.push_back(start_vertex);
    while (!queue.empty()) {
        Vertex v = queue[0];
        if (vector_contains(walk_v, v)) {
            queue.erase(queue.begin());
            continue;
        }
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
}

// алгоритм Беллмана-Форда
vector<vector<int>> Graph::shortest_path_Ford(int id_from, int id_to) const {

    int index_from = find_vertex(id_from);
    int index_to = find_vertex(id_to);
    if (index_from == -1 || index_to == -1) {
        throw "Vertex not found";
    }
    vector<int> path;
    vector<int> distance(graph.size(), INT_MAX);
    vector<int> p (graph.size(), -1);
    std::vector<int> result_path;



    distance[index_from] = 0;
    for (int i = 0; i < graph.size() - 1; i++) {
        for (int j = 0; j < graph.size(); j++) {
            vector<Edge> edges = graph[j].edge;
            for (int k = 0; k < edges.size(); k++) {
                int index = find_vertex(edges[k].id);
                if (distance[j] != INT_MAX && distance[j] + edges[k].weight < distance[index]) {
                    distance[index] = distance[j] + edges[k].weight;
                    p[index] = j;

                }
            }
        }
    }
    for (int j = 0; j < graph.size(); j++) {
        vector<Edge> edges = graph[j].edge;
        for (int k = 0; k < edges.size(); k++) {
            int index = find_vertex(edges[k].id);
            if (distance[j] != INT_MAX && distance[j] + edges[k].weight < distance[index]) {
                throw "Negative cycle";
            }
        }
    }

    // восстановление пути
    int index = index_to;
    while (index != index_from) {
        path.push_back(index);
        index = p[index];
    }
    path.push_back(index_from);

    for (int i = path.size() - 1; i >= 0; i--) {
        result_path.push_back(graph[path[i]].id);
    }

    vector<vector<int >> itog = {result_path, distance};
    return itog;


}

// Задача № 3
vector<int> Graph::max_average_length() const {
    vector<int> result ;
    int max_length = 0;
    int max_length_id = 0;
    int max_id = -1;
    vector <int> v;
    for (int i=0; i < graph.size(); i++){
        v.clear();
        max_length_id = 0;
        vector<Edge> edge = graph[i].edge;
        if (!edge.empty()){


        for (int j = 0 ; j<edge.size();j++){
            if (find_vertex(edge[j].id) != find_vertex(graph[i].id)) {
                max_length_id += edge[j].weight;
                v.push_back(edge[j].id);
            }
        }
        }
        for (int k = 0 ; k<graph.size();k++){
            vector<Edge> edge2 = graph[k].edge;
            if(graph[k].id != graph[i].id && !edge2.empty() && !vector_contains_2(v, graph[k].id)) {

                for (int l = 0; l < edge2.size(); l++) {
                    if (edge2[l].id == graph[i].id) {
                        max_length_id += edge2[l].weight;
                    }
                }
            }
        }
       if  (max_length_id>= max_length){
            max_length = max_length_id;
            max_id = i;
       }
    }
    result.push_back(graph[max_id].id);
    result.push_back(max_length);
    return result;
}

void Graph::vertices(vector<int> &v) const {
    for(const auto & i : graph){
        v.push_back(i.id);
    }
}


















