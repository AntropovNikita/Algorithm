#include <iostream>
#include <stdint.h>
#include <vector>
#include <queue>

using namespace std;

/**
 * @brief Перечисление возможных цветов
*/
enum class Color : char
{
    UNCOLORED = -1, /** Нет цвета */
    RED_COLOR = 0,  /** Красный цвет */
    BLUE_COLOR = 1  /** Синий цвет */
};

/**
 * @brief Перечисления состояний вершин графа
*/
enum class State : char
{
    CLOSE_STATE, /** Вершина не обнаружена */
    OPEN_STATE,  /** Вершина обнаружена */
    READY_STATE  /** Вершина обработана */
};

/**
 * @brief Вершина графа
*/
struct Node
{
    vector<size_t> edges;             /** Список соседних вершин */
    Color color = Color::UNCOLORED;   /** Цвет вершины */
    State state = State::CLOSE_STATE; /** Состояние вершины */
};

/**
 * @brief Структура данных для графа
*/
typedef vector<Node> Graph;

/**
 * @brief Инициализация графа
 * @param[out] graph Ссылка на граф
*/
void init_graph(Graph& graph);

/**
 * @brief Выбор цвета текущей вершине на основе цвета вершины соседа
 * @param[in] color Цвет вершины соседа
 * @return Элемент перечисления Color
*/
Color choose_color(Color color);

/**
 * @brief Поиск в ширину по заданному графу
 * @param[out] graph Ссылка на граф
 * @param[in] node Номер стартовой вершины
 * @return true, если граф двудольный, false иначе
*/
bool bfs(Graph& graph, size_t node);

/**
 * @brief Раскраска графа
 * @param[out] graph Ссылка на граф
 * @return true, если граф двудольный, false иначе
*/
bool color_graph(Graph& graph);

int main()
{
    size_t n; // Кол-во вершин
    cin >> n;

    Graph graph(n);
    init_graph(graph); // Инициализация графа

    if (color_graph(graph)) // Если граф двудольный, вывести коды цвета вершин
        for(auto node : graph)
            cout << static_cast<int16_t>(node.color);
    else
        cout << -1;
    
    return 0;
}

void init_graph(Graph& graph)
{
    for(auto node = graph.begin(); node != graph.end(); node++) // Перебор вершин графа
    {
        size_t next_edge;
        while (true) // Добавление вершин в список смежности к текущей вершине
        {
            cin >> next_edge;
            if (next_edge == 0) // Конец ввода
                break;
            node->edges.push_back(next_edge - 1);
            graph[next_edge-1].edges.push_back(node - graph.begin());
        }
    }
}

Color choose_color(Color color)
{
    if (color == Color::RED_COLOR) return Color::BLUE_COLOR;
    if (color == Color::BLUE_COLOR) return Color::RED_COLOR;
    return Color::UNCOLORED;
}

bool bfs(Graph& graph, size_t node)
{
    queue<size_t> to_visit; // Инициализация очереди и добавление стартовой вершины
    to_visit.push(node);
    graph[node].state = State::OPEN_STATE;

    while (!to_visit.empty()) // Пока очередь не пустая
    {
        size_t cur_node = to_visit.front(); // Достаем из очереди следующую вершину
        to_visit.pop();
        graph[cur_node].state = State::READY_STATE;

        for(auto edge : graph[cur_node].edges) // Перебор соседей текущей вершины
        {
            if (graph[edge].state == State::OPEN_STATE &&   // Если текущая вершина уже обнаружена
                graph[edge].color == graph[cur_node].color) // и ее цвет совпадает с цветом текущей вершины, то
                return false;                               // граф не двудольный
            if (graph[edge].state == State::CLOSE_STATE)
            {
                graph[edge].color = choose_color(graph[cur_node].color); // Выбор цвета
                graph[edge].state = State::OPEN_STATE; // Помещение вершины в очередь
                to_visit.push(edge);
            }
        }
    }

    return true;
}

bool color_graph(Graph& graph)
{
    for(auto node = graph.begin(); node != graph.end(); node++) // Перебор вершин 
    {
        if (node->state == State::CLOSE_STATE) // Если вершина еще не обнаружена
        {
            node->color = Color::RED_COLOR; // Раскрасить вершину и выхвать поиск в ширину
            if (!bfs(graph, node - graph.begin())) // Если подграф не двудольный, то вернуть false
                return false;
        }
    }

    return true;
}