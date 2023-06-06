#include <iostream>
#include "Graph.h"
static vector<Vertex> visited;
using namespace std;

void getch_(){
    cout << "Press any key to continue...";
    getchar();
    getchar();
}

void clear_monitor(){
    system("clear");
}

void create_graph(int size, Graph &graph){
    int id;
    int id_from;
    int id_to;
    int weight;
    for (int i = 0; i < size; i++){
        cout << "Введите id вершины: ";
        cin >> id;
        graph.add_vertex(id);
    }
    cout << "Введите количество ребер: ";
    cin >> size;
    for (int i = 0; i < size; i++){
        cout << "Введите id вершины, из которой выходит ребро: ";
        cin >> id_from;
        if (graph.find_vertex(id_from)==-1){
            cout << "Вершины с таким id не существует" << endl;
            i--;
            continue;
        }
        cout << "Введите id вершины, в которую входит ребро: ";
        cin >> id_to;
        if (graph.find_vertex(id_to)==-1){
            cout << "Вершины с таким id не существует" << endl;
            i--;
            continue;
        }
        cout << "Введите вес ребра: ";
        cin >> weight;
        graph.add_edge(id_from, id_to, weight);
    }
}

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

    while (true){
    clear_monitor();
    cout << "Меню:" << endl;
    cout << "1. Добавить вершину" << endl;
    cout << "2. Добавить ребро" << endl;
    cout << "3. Удалить вершину" << endl;
    cout << "4. Удалить ребро" << endl;
    cout << "5. Вывести граф" << endl;
    cout << "6. Найти кратчайший путь" << endl;
    cout << "7. Найти вершину с максимальным средним весом ребер" << endl;
    cout << "8. Обход в ширину" << endl;
    cout << "9. Создать граф" << endl;
    cout << "Выберите действие: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Введите id вершины: ";
            cin >> id;
            if (graph.add_vertex(id)) {
                cout << "----Вершина добавлена----" << endl;
                getch_();
            } else {
                cout << "----Вершина не добавлена----" << endl;
                getch_();
            }
            break;
        case 2:
            cout << "----Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "----Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            cout << "----Введите вес ребра: ";
            cin >> weight;
            if (graph.add_edge(id_from, id_to, weight)) {
                cout << "----Ребро добавлено" << endl;
                getch_();
            } else {
                cout << "----Ребро не добавлено" << endl;
                getch_();
            }
            break;
        case 3:
            cout << "Введите id вершины: ";
            cin >> id;
            if (graph.delete_vertex(id)) {
                cout << "Вершина удалена" << endl;
                getch_();
            } else {
                cout << "Вершина не удалена" << endl;
                getch_();
            }
            break;
        case 4:
            cout << "Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            if (graph.delete_edge(id_from, id_to)) {
                cout << "Ребро удалено" << endl;
                getch_();
            } else {
                cout << "Ребро не удалено" << endl;
                getch_();
            }
            break;
        case 5:
            graph.print();
            getch_();
            break;
        case 6:
            cout << "Введите id вершины, из которой выходит ребро: ";
            cin >> id_from;
            cout << "Введите id вершины, в которую входит ребро: ";
            cin >> id_to;
            path = graph.shortest_path_Ford(id_from, id_to);
            if (path.size() == 0) {
                cout << "Путь не найден" << endl;
                getch_();
            } else {
                cout << "Кратчайший путь: ";
                for (int i = 0; i < path.size(); i++) {
                    for (int j = 0; j < path[i].size(); j++) {
                        cout << path[i][j] << " ";
                    }
                    cout << endl;
                    getch_();
                }
            }
            break;
        case 7:
            max = graph.max_average_length();
            if (max.empty()) {
                cout << "Вершина не найдена" << endl;
                getch_();
            } else {
                cout << "Вершина с максимальным средним весом ребер: ";
                for (int i = 0; i < max.size(); i++) {
                    cout << max[i] << " ";
                }
                cout << endl;
                getch_();
            }
            break;
        case 8:
            cout << "Введите id вершины: ";
            cin >> id;
            graph.walk_bfs(graph.find_vertex(id), [](const Vertex &vertex) {
                cout << vertex.id << endl;
                visited.push_back(vertex);
                return visited;
            });
            getch_();
            break;
        case 9:
            // ввод размер графа
            int size;
            cout << "Введите размер графа: ";
            cin >> size;
            create_graph(size, graph);
            cout<< "----Граф создан----" << endl;
            getch_();
            break;
    }
    }
}


int main() {
    std::function<vector<Vertex>(const Vertex& )> action;

    Graph graph;
    menu(graph);
    return 0;


}
