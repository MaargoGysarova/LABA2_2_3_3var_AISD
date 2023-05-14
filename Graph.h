#ifndef LABA2_2_3_3VAR_AISD_GRAPH_H
#define LABA2_2_3_3VAR_AISD_GRAPH_H
#include <vector>
using namespace std;

struct Edge{
    Edge* next;
    int weight;
    int id;
    Edge(int id, int weight){
        this->id = id;
        this->weight = weight;
        next = nullptr;
    }
};

struct Vertex{
        Edge * edge;
        int id;
        int color;
};

class Graph {
private:
    vector<Vertex> graph;
public:
    ~Graph(); // ��������
    int find_vertex(int id); //�஢�ઠ ������ ���設�
    bool add_vertex(int id); //���������� ���設�
    bool delete_vertex(int id); //�������� ���設�

    bool find_edge(int id_from, int id_to); //�஢�ઠ ������ ॡ�
    void add_edge(int id_from, int id_to, int weight); //���������� ॡ�
    void delete_edge(int id_from, int id_to); //�������� ॡ�

    vector<Edge> edges(const Vertex& vertex);//����祭�� ��� ॡ��, ��室��� �� ���設�

    //���� ���砩襣� ���
    vector<Edge> shortest_path(const Vertex& from,const Vertex& to) const;

    size_t order() const; //���冷�
    size_t degree() const; //�⥯���

    void print() const; //�뢮� ���

    vector<Vertex>  walk(const Vertex& start_vertex)const;

};


#endif //LABA2_2_3_3VAR_AISD_GRAPH_H
