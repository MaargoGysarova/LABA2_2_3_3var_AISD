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
        vector <Edge> edge;
        int id;
        int color;
        explicit Vertex(int id){
            this->id = id;
            edge = nullptr;
            color = 0;
        }
};

class Graph {
private:
    vector<Vertex> graph;
public:
    ~Graph(); // Деструктор
    int find_vertex(int id); //Проверка наличия вершины
    bool add_vertex(int id); //Добавление вершины
    bool delete_vertex(int id); //Удаление вершины

    bool find_edge(int id_from, int id_to); //Проверка наличия ребра
    bool add_edge(int id_from, int id_to, int weight); //Добавление ребра
    bool delete_edge(int id_from, int id_to); //Удаление ребра

    vector<Edge>& edges(const Vertex& vertex);//получение всех ребер, выходящих из вершины по ссылке


    //поиск кратчайшего пути
    vector<Edge> shortest_path(const Vertex& from,const Vertex& to) const;

    size_t order() const; //порядок
    size_t degree() const; //степень

    void print() const; //вывод графа

    vector<Vertex>  walk(const Vertex& start_vertex)const;

};


#endif //LABA2_2_3_3VAR_AISD_GRAPH_H
