#include <iostream>
#include "Graph.h"
static vector<Vertex> visited;
using namespace std;

//меню для работы с графом
void menu(Graph& graph){
    int choice;
    int id;
    int id_from;
    int id_to;
    int weight;
    vector<int> v;
    vector<vector<int>> path;
    vector<int> max;
    cout << "1. Добавить вершину" << endl;
    cout << "2. Добавить ребро" << endl;
    cout << "3. Удалить вершину" << endl;
    cout << "4. Удалить ребро" << endl;
    cout << "5. Вывести граф" << endl;
    cout << "6. Найти кратчайший путь" << endl;
    cout << "7. Найти вершину с максимальным средним весом ребер" << endl;
    cout << "8. Обход в ширину" << endl;
    cout << "9. Вывести вершины графа" << endl;
    cout << "Выберите действие: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Введите id вершины: ";
            cin >> id;
            if (graph.add_vertex(id)) {
                cout << "Вершина добавлена" << endl;
            } else {
                cout << "Вершина не добавлена" << endl;
            }
            break;
        case 2:
            cout << "Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            cout << "Введите вес ребра: ";
            cin >> weight;
            if (graph.add_edge(id_from, id_to, weight)) {
                cout << "Ребро добавлено" << endl;
            } else {
                cout << "Ребро не добавлено" << endl;
            }
            break;
        case 3:
            cout << "Введите id вершины: ";
            cin >> id;
            if (graph.delete_vertex(id)) {
                cout << "Вершина удалена" << endl;
            } else {
                cout << "Вершина не удалена" << endl;
            }
            break;
        case 4:
            cout << "Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            if (graph.delete_edge(id_from, id_to)) {
                cout << "Ребро удалено" << endl;
            } else {
                cout << "Ребро не удалено" << endl;
            }
            break;
        case 5:
            graph.print();
            break;
        case 6:
            cout << "Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            path = graph.shortest_path_Ford(id_from, id_to);
            if (path.size() == 0) {
                cout << "Путь не найден" << endl;
            } else {
                cout << "Кратчайший путь: ";
                for (int i = 0; i < path.size(); i++) {
                    for (int j = 0; j < path[i].size(); j++) {
                        cout << path[i][j] << " ";
                    }
                    cout << endl;
                }
            }
            break;
        case 7:
            max = graph.max_average_length();
            if (max.empty()) {
                cout << "Вершина не найдена" << endl;
            } else {
                cout << "Вершина с максимальным средним весом ребер: ";
                for (int i = 0; i < max.size(); i++) {
                    cout << max[i] << " ";
                }
                cout << endl;
            }
            break;
        case 8:
            cout << "Введите id вершины: ";
            cin >> id;
            graph.walk_bfs(graph.find_vertex(id), [](const Vertex& vertex){
                cout << vertex.id << endl;
                visited.push_back(vertex);
                return visited;
            });
            break;
        case 9:
            vector<int> vertices;
            vertices.clear();
            graph.vertices(vertices);
            cout << "Вершины графа: ";
            for (int i = 0; i < v.size(); i++) {
                cout << v[i] << " ";
            }
            cout << endl;
            break;
        default:
            cout << "Неверный ввод" << endl;
            break;
    }
}


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
    vector<int> path = graph.shortest_path_Ford(10, 60)[0];
    cout << endl;
    vector<int> distance_all =  graph.shortest_path_Ford(10, 60)[1];
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
