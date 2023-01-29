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
    Edgenode(size_t A, size_t B, uint16_t C)
    {
        this->A = A;
        this->B = B;
        this->C = C;
    }

    size_t A, B; /** Номера вершин ребра */
    uint16_t C;  /** Вес ребра */
};

/**
 * @brief Описание графа
*/
struct Graph
{
    /** 
     * @brief Конструктор графа
    */
    Graph(size_t vertex) { this->F.resize(vertex, -1); }

    vector<Edgenode> edges; /** Массив ребер */
    vector<int32_t> F;     /** Массив функционала */
};

/**
 * @brief Инициализация графа
 * @param[out] Указатель на граф
 * @param[in] m Кол-во ребер
*/
void init_graph(Graph* graph, size_t m);

/**
 * @brief Алгоритм Форд-Беллмана для поиска наиболее длинного пути
 * @param[out] graph Указатель на граф
 * @param[in] out_vertex Конечная вершина
 * @return true, если путь до конечной вершины существует, иначе false
*/
bool ford_bellman(Graph* graph, size_t out_vetex);

int main()
{
    size_t n, m, s, f;
    cin >> n >> m;

    Graph graph(n);

    init_graph(&graph, m);
    cin >> s >> f;
    graph.F[s-1] = 0;

    if (ford_bellman(&graph, f-1))
        cout << graph.F[f-1];
    else
        cout << "No solution";

    return 0;
}

void init_graph(Graph* graph, size_t m)
{
    size_t A, B;
    uint16_t C;
    for(size_t i=0; i < m; i++)
    {
        cin >> A >> B >> C;
        graph->edges.push_back(Edgenode(A-1, B-1, C));
    }
}

bool ford_bellman(Graph* graph, size_t out_vetex)
{   
    size_t n = graph->F.size() - 1;
    for(size_t i=0; i < n; i++) // Обход графа по всем ребрам V-1 раз, где V - кол-во вершин
        for(auto edge : graph->edges)
            if (graph->F[edge.A] != -1 && graph->F[edge.B] < graph->F[edge.A] + edge.C)
                graph->F[edge.B] = graph->F[edge.A] + edge.C; // Расчет максимального значения

    if (graph->F[out_vetex] == -1) // Проверка, дошли ли до конечной вершины
            return false;
    return true;
}