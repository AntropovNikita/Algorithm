#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;


/**
 * @brief Описание ребра графа
*/
struct Edgenode
{
    /**
     * @brief Конструктор ребра
    */
    Edgenode(size_t A, size_t B, double rate, double com)
    {
        this->A = A;
        this->B = B;
        this->rate = rate;
        this->com = com;
    }

    size_t A, B; /** Номера вершин ребра */
    double rate, com; /** Значения для обмена валют */
};

/**
 * @brief Описание графа
*/
struct Graph
{
    /** 
     * @brief Конструктор графа
    */
    Graph(size_t vertex) { this->F.resize(vertex); }

    vector<Edgenode> edges; /** Массив ребер */
    vector<double> F; /** Массив функционала */
};

/**
 * @brief Инициализация графа
 * @param[out] Указатель на граф
 * @param[in] m Кол-во разменных пунктов
*/
void init_graph(Graph* graph, size_t m);

/**
 * @brief Алгоритм Форд-Беллмана для поиска наиболее длинного пути
 * @param[out] graph Указатель на граф
 * @return true, если отрицательных циклов нет, иначе false
*/
bool ford_bellman(Graph* graph);

int main()
{
    size_t m, n, s;
    double v;
    cin >> n >> m >> s >> v;

    Graph graph(n);
    graph.F[s-1] = v; // Начальное кол-во валюты s

    init_graph(&graph, m);

    if (ford_bellman(&graph))
        cout << "YES";
    else
        cout << "NO";

    return 0;
}

void init_graph(Graph* graph, size_t m)
{
    size_t A, B;
    double RAB, CAB, RBA, CBA;
    for(size_t i=0; i < m; i++)
    {
        cin >> A >> B >> RAB >> CAB >> RBA >> CBA;
        graph->edges.push_back(Edgenode(A-1, B-1, RAB, CAB));
        graph->edges.push_back(Edgenode(B-1, A-1, RBA, CBA));
    }
}

bool ford_bellman(Graph* graph)
{   
    for(size_t i=0; i < graph->F.size()-1; i++) // Обход графа по всем ребрам V-1 раз, где V - кол-во вершин
        for(auto edge : graph->edges)
            graph->F[edge.B] = max(graph->F[edge.B], (graph->F[edge.A] - edge.com)*edge.rate); // Расчет максимального значения

    for(auto edge : graph->edges) // Проверка на отрицательные циклы
        if ((graph->F[edge.A] - edge.com)*edge.rate > graph->F[edge.B])
            return true;
    return false;
}