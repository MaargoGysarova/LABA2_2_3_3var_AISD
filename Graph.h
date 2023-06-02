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
    ~Graph(); // Деструктор
    [[nodiscard]] int find_vertex(int id) const; //Проверка наличия вершины
    bool add_vertex(int id); //Добавление вершины
    bool delete_vertex(int id); //Удаление вершины

    bool find_edge(int id_from, int id_to); //Проверка наличия ребра
    bool add_edge(int id_from, int id_to, int weight); //Добавление ребра
    bool delete_edge(int id_from, int id_to); //Удаление ребра

    vector<Edge>& edges(const Vertex& vertex);//получение всех ребер, выходящих из вершины по ссылке

    [[nodiscard]] size_t order() const; //порядок
    [[nodiscard]] size_t degree() const; //степень

    void print() const; //вывод графа

    void walk_bfs(int index_v, const function<vector<Vertex>(const Vertex&)>& action)const; // обход в ширину


    [[nodiscard]] vector<vector<int>> shortest_path_Ford(int id_from, int id_to) const; // Нахождения кратчайшего пути по Форду
    [[nodiscard]] vector<int> max_average_length() const; // нахождение Вершины с максимальным числом веса смежных ребер Задача №3
};


#endif //LABA2_2_3_3VAR_AISD_GRAPH_H
