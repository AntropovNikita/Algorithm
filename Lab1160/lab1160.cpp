#include <iostream>
#include <vector>
#include <queue>
#include <stdint.h>

using namespace std;

/**
 * @brief Описание ребра графа
*/
struct Edgenode
{
    /** 
     * @brief Конструктор
    */
    Edgenode(uint32_t w, size_t vertex1, size_t vertex2) 
    {
        this->weight = w; 
        this->vertex1 = vertex1; 
        this->vertex2 = vertex2; 
    }

    /**
     * @brief Перегузка оператора сравнения для очереди с приоритетом
    */
    friend bool operator< (Edgenode const& lhs, Edgenode const& rhs) 
    {
        return lhs.weight > rhs.weight;
    }

    uint32_t weight; /** Вес ребра */
    size_t vertex1; /** Номер первой вершины */
    size_t vertex2; /** Номер второй вершины */
};

/**
 * @brief Описание графа
*/
struct Graph
{
    /**
     * @brief Конструктор
    */
    Graph(size_t edges, size_t vertex)
    {
        this->edge_n = edges;
        this->vertex_n = vertex;
    }

    priority_queue<Edgenode> edges; /** Очередь с ребрами */
    size_t vertex_n; /** Кол-во вершин */
    size_t edge_n; /** Кол-во ребер */
};

/**
 * @brief Структура множества для организации операций поиска и объединения в минимальном остовном дереве
*/
struct SetUnion
{
    /**
     * @brief Конструктор
    */
    SetUnion(size_t union_n)
    {
        this->union_n = union_n;
        this->parent.reserve(union_n);
        this->subtree_n.reserve(union_n);

        for(size_t i=0; i < union_n; i++) // 
        {
            this->parent[i] = i;
            this->subtree_n[i] = 1;
        }
    }

    vector<size_t> parent; /** Массив с номерами родителей вершин */
    vector<size_t> subtree_n; /** Кол-во элементов в поддереве текущей вершины */
    size_t union_n; /** Общее кол-во элементов в множестве */
};

/**
 * @brief Инициализация графа
 * @param[out] graph Указатель на граф
*/
void init_graph(Graph* graph);

/**
 * @brief Рекурсивный поиск корня дерева, содержащего заданную вершину
 * @param[in] set_union Множество с остовными деревьями
 * @param[in] vertex Номер вершины
 * @return Номер корня дерева
*/
size_t find(SetUnion* set_union, size_t vertex);

/**
 * @brief Проверка, принадлежат ли две вершины одному дереву
 * @param[in] set_union Множество с остовными деревьями
 * @param[in] vertex1 Номер первой вершины
 * @param[in] vertex2 Номер второй вершины
 * @return true, если вершины отнсоятся к одному дереву, иначе false
*/
bool same_component(SetUnion* set_union, size_t vertex1, size_t vertex2);

/**
 * @brief Объединение двух деревьев в одно
 * @param[in] set_union Множество с остовными деревьями
 * @param[in] vertex1 Номер первой вершины
 * @param[in] vertex2 Номер второй вершины
 * @return Номер корня нового дерева
*/
size_t union_component(SetUnion* set_union, size_t vertex1, size_t vertex2);

/**
 * @brief Алгоритм Крускала для построения минимального остовного дерева
 * @param[in] graph Указатель на граф
*/
void kruskal(Graph* graph);

int main()
{
    size_t all_hubs, hubs_conn;
    cin >> all_hubs >> hubs_conn;

    Graph graph(hubs_conn, all_hubs);
    init_graph(&graph);

    kruskal(&graph);

    return 0;
}

void init_graph(Graph* graph)
{
    size_t first, second;
    uint32_t weight;
    for(size_t i=0; i < graph->edge_n; i++)
    {
        cin >> first >> second >> weight;
        graph->edges.push(Edgenode(weight, first, second));
    }
}

size_t find(SetUnion* set_union, size_t vertex)
{
    if (set_union->parent[vertex] == vertex) // Если вершина не имеет родителя
        return vertex;
    return find(set_union, set_union->parent[vertex]);
}

bool same_component(SetUnion* set_union, size_t vertex1, size_t vertex2)
{
    return (find(set_union, vertex1) == find(set_union, vertex2));
}

size_t union_component(SetUnion* set_union, size_t vertex1, size_t vertex2)
{
    size_t root1 = find(set_union, vertex1);
    size_t root2 = find(set_union, vertex2);
    if (root1 == root2) // Проверка, принадлежат ли вершины одному дереву
        return root1;

    if (set_union->subtree_n[root1] >= set_union->subtree_n[root2]) // Минимизация высоты итогового дерева
    {
        set_union->subtree_n[root1] += set_union->subtree_n[root2];
        set_union->parent[root2] = root1;
        return root1;
    }
    else
    {
        set_union->subtree_n[root2] += set_union->subtree_n[root1];
        set_union->parent[root1] = root2;
        return root2;
    }
}

void kruskal(Graph* graph)
{
    SetUnion set_union(graph->vertex_n);
    vector<Edgenode> tree; // Массив ребер, которые принадлежат остовному дереву
    uint32_t max_weight = 0; // Максимальный вес ребра в остовном дерева

    while (!graph->edges.empty())
    {
        Edgenode edge = graph->edges.top();
        graph->edges.pop();

        if (!same_component(&set_union, edge.vertex1 - 1, edge.vertex2 - 1))
        {
            union_component(&set_union, edge.vertex1 - 1, edge.vertex2 - 1);
            tree.push_back(edge);
            max_weight = max(max_weight, edge.weight);
        }
    }

    cout << max_weight << '\n';
    cout << tree.size() << "\n";
    for(auto edge : tree)
        cout << edge.vertex1 << " " << edge.vertex2 << "\n";
}