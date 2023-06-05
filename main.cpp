#include <iostream>
#include "Graph.h"
static vector<Vertex> visited;
using namespace std;

//���� ��� ࠡ��� � ��䮬
void menu(Graph& graph){
    int choice;
    int id;
    int id_from;
    int id_to;
    int weight;
    vector<int> v;
    vector<vector<int>> path;
    vector<int> max;
    cout << "1. �������� ���設�" << endl;
    cout << "2. �������� ॡ�" << endl;
    cout << "3. ������� ���設�" << endl;
    cout << "4. ������� ॡ�" << endl;
    cout << "5. �뢥�� ���" << endl;
    cout << "6. ���� ���砩訩 ����" << endl;
    cout << "7. ���� ���設� � ���ᨬ���� �।��� ��ᮬ ॡ��" << endl;
    cout << "8. ��室 � �ਭ�" << endl;
    cout << "9. �뢥�� ���設� ���" << endl;
    cout << "�롥�� ����⢨�: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "������ id ���設�: ";
            cin >> id;
            if (graph.add_vertex(id)) {
                cout << "���設� ���������" << endl;
            } else {
                cout << "���設� �� ���������" << endl;
            }
            break;
        case 2:
            cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            cout << "������ ��� ॡ�: ";
            cin >> weight;
            if (graph.add_edge(id_from, id_to, weight)) {
                cout << "���� ���������" << endl;
            } else {
                cout << "���� �� ���������" << endl;
            }
            break;
        case 3:
            cout << "������ id ���設�: ";
            cin >> id;
            if (graph.delete_vertex(id)) {
                cout << "���設� 㤠����" << endl;
            } else {
                cout << "���設� �� 㤠����" << endl;
            }
            break;
        case 4:
            cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            if (graph.delete_edge(id_from, id_to)) {
                cout << "���� 㤠����" << endl;
            } else {
                cout << "���� �� 㤠����" << endl;
            }
            break;
        case 5:
            graph.print();
            break;
        case 6:
            cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            path = graph.shortest_path_Ford(id_from, id_to);
            if (path.size() == 0) {
                cout << "���� �� ������" << endl;
            } else {
                cout << "���砩訩 ����: ";
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
                cout << "���設� �� �������" << endl;
            } else {
                cout << "���設� � ���ᨬ���� �।��� ��ᮬ ॡ��: ";
                for (int i = 0; i < max.size(); i++) {
                    cout << max[i] << " ";
                }
                cout << endl;
            }
            break;
        case 8:
            cout << "������ id ���設�: ";
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
            cout << "���設� ���: ";
            for (int i = 0; i < v.size(); i++) {
                cout << v[i] << " ";
            }
            cout << endl;
            break;
        default:
            cout << "������ ����" << endl;
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
    cout << "����� ���砩襣� ���: " << distance_all[5] << endl;
    cout << "���砩訩 ����: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    cout << endl << "���砩訥 ��� �� ��� ���設:" << endl;
    for (int i = 0; i < distance_all.size(); i++) {
        cout << distance_all[i] << " ";
    }
    vector<int > V = graph.max_average_length();
    cout << endl;
    cout << "���設� � ���ᨬ���� ��ᮬ ॡ��: " << V[0] << endl;
    cout << "��� ॡ��: " << V[1] << endl;


    return 0;


}
