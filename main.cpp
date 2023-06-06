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
        cout << "������ id ���設�: ";
        cin >> id;
        graph.add_vertex(id);
    }
    cout << "������ ������⢮ ॡ��: ";
    cin >> size;
    for (int i = 0; i < size; i++){
        cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
        cin >> id_from;
        if (graph.find_vertex(id_from)==-1){
            cout << "���設� � ⠪�� id �� �������" << endl;
            i--;
            continue;
        }
        cout << "������ id ���設�, � ������ �室�� ॡ�: ";
        cin >> id_to;
        if (graph.find_vertex(id_to)==-1){
            cout << "���設� � ⠪�� id �� �������" << endl;
            i--;
            continue;
        }
        cout << "������ ��� ॡ�: ";
        cin >> weight;
        graph.add_edge(id_from, id_to, weight);
    }
}

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

    while (true){
    clear_monitor();
    cout << "����:" << endl;
    cout << "1. �������� ���設�" << endl;
    cout << "2. �������� ॡ�" << endl;
    cout << "3. ������� ���設�" << endl;
    cout << "4. ������� ॡ�" << endl;
    cout << "5. �뢥�� ���" << endl;
    cout << "6. ���� ���砩訩 ����" << endl;
    cout << "7. ���� ���設� � ���ᨬ���� �।��� ��ᮬ ॡ��" << endl;
    cout << "8. ��室 � �ਭ�" << endl;
    cout << "9. ������� ���" << endl;
    cout << "�롥�� ����⢨�: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "������ id ���設�: ";
            cin >> id;
            if (graph.add_vertex(id)) {
                cout << "----���設� ���������----" << endl;
                getch_();
            } else {
                cout << "----���設� �� ���������----" << endl;
                getch_();
            }
            break;
        case 2:
            cout << "----������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "----������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            cout << "----������ ��� ॡ�: ";
            cin >> weight;
            if (graph.add_edge(id_from, id_to, weight)) {
                cout << "----���� ���������" << endl;
                getch_();
            } else {
                cout << "----���� �� ���������" << endl;
                getch_();
            }
            break;
        case 3:
            cout << "������ id ���設�: ";
            cin >> id;
            if (graph.delete_vertex(id)) {
                cout << "���設� 㤠����" << endl;
                getch_();
            } else {
                cout << "���設� �� 㤠����" << endl;
                getch_();
            }
            break;
        case 4:
            cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            if (graph.delete_edge(id_from, id_to)) {
                cout << "���� 㤠����" << endl;
                getch_();
            } else {
                cout << "���� �� 㤠����" << endl;
                getch_();
            }
            break;
        case 5:
            graph.print();
            getch_();
            break;
        case 6:
            cout << "������ id ���設�, �� ���ன ��室�� ॡ�: ";
            cin >> id_from;
            cout << "������ id ���設�, � ������ �室�� ॡ�: ";
            cin >> id_to;
            path = graph.shortest_path_Ford(id_from, id_to);
            if (path.size() == 0) {
                cout << "���� �� ������" << endl;
                getch_();
            } else {
                cout << "���砩訩 ����: ";
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
                cout << "���設� �� �������" << endl;
                getch_();
            } else {
                cout << "���設� � ���ᨬ���� �।��� ��ᮬ ॡ��: ";
                for (int i = 0; i < max.size(); i++) {
                    cout << max[i] << " ";
                }
                cout << endl;
                getch_();
            }
            break;
        case 8:
            cout << "������ id ���設�: ";
            cin >> id;
            graph.walk_bfs(graph.find_vertex(id), [](const Vertex &vertex) {
                cout << vertex.id << endl;
                visited.push_back(vertex);
                return visited;
            });
            getch_();
            break;
        case 9:
            // ���� ࠧ��� ���
            int size;
            cout << "������ ࠧ��� ���: ";
            cin >> size;
            create_graph(size, graph);
            cout<< "----��� ᮧ���----" << endl;
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
