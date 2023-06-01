#ifndef LABA2_2_3_3VAR_AISD_GRAPH_H
#define LABA2_2_3_3VAR_AISD_GRAPH_H
#include <vector>
#include <functional>
using namespace std;

struct Edge{
    Edge* next;
    int weight;
    int id;
    int color;
    Edge(int id, int weight){
        this->id = id;
        this->weight = weight;
        next = nullptr;
        color = 0;
    }
};

struct Vertex{
        vector <Edge> edge;
        int id;
        int color;
        explicit Vertex(int id){
            this->id = id;
            edge = vector<Edge>();
            color = 0;
        }
};

class Graph {
private:
    vector<Vertex> graph;
public:
    ~Graph(); // ��������
    int find_vertex(int id) const; //�஢�ઠ ������ ���設�
    bool add_vertex(int id); //���������� ���設�
    bool delete_vertex(int id); //�������� ���設�

    bool find_edge(int id_from, int id_to); //�஢�ઠ ������ ॡ�
    bool add_edge(int id_from, int id_to, int weight); //���������� ॡ�
    bool delete_edge(int id_from, int id_to); //�������� ॡ�

    vector<Edge>& edges(const Vertex& vertex);//����祭�� ��� ॡ��, ��室��� �� ���設� �� ��뫪�


    //���� ���砩襣� ���


    size_t order() const; //���冷�
    size_t degree() const; //�⥯���

    void print() const; //�뢮� ���

    vector<Vertex>  walk_bfs(int index_v, const function<vector<Vertex>(const Vertex&)>& action)const;


    vector<int> shortest_path(int id_from, int id_to) const;

    int max_average_length() const;
};


#endif //LABA2_2_3_3VAR_AISD_GRAPH_H
