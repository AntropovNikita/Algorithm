#include <iostream>
#include <array>
#include <stdint.h>

#define MAX_N 8 // Кол-во вершин куба

using namespace std;

/**
 * @brief Вершина куба
*/
struct Node
{
    char name;      /** Обозначение вершины */
    uint16_t duons; /** Кол-во дуонов */
};

/**
 * @brief Вывод действия
 * @param[in] first Обозначение первой вершины
 * @param[in] second Обозначение второй вершины
 * @param[in] act Действие
*/
void print_act(char first, char second, char act);

/**
 * @brief Уменьшение дуонов в двух смежных вершинах
 * @param[in] nodes Массив с вершинами
 * @param[in] first Индекс вершины куба
 * @param[in] second Индекс смежной вершины
*/
void del(array<Node, MAX_N>& nodes, size_t first, size_t second);

/**
 * @brief Увеличение дуонов в двух смежных вершинах
 * @param[in] nodes Массив с вершинами
 * @param[in] first Индекс вершины куба
 * @param[in] second Индекс смежной вершины
*/
void create(array<Node, MAX_N>& nodes, size_t first, size_t second, uint16_t duons);

int main()
{
    array<Node, MAX_N> nodes = {{
        {'A', 0}, 
        {'B', 0}, 
        {'C', 0},
        {'D', 0},
        {'E', 0},
        {'F', 0},
        {'G', 0},
        {'H', 0}
    }};

    // Инициализация дуонов
    for(size_t i=0; i < MAX_N; i++)
        cin >> nodes[i].duons;

    // Проверка условия A+C+F+H == B+D+E+G
    if ((nodes[0].duons + nodes[2].duons + nodes[5].duons + nodes[7].duons) != 
        (nodes[1].duons + nodes[3].duons + nodes[4].duons + nodes[6].duons))
        cout << "IMPOSSIBLE";
    else
    {
        // Вершина A
        del(nodes, 0, 1);
        del(nodes, 0, 3);
        del(nodes, 0, 4);
        if (nodes[0].duons > 0)
        {
            create(nodes, 1, 2, nodes[0].duons);
            del(nodes, 0, 1);
        }

        // Вершина B
        del(nodes, 1, 2);
        del(nodes, 1, 5);
        if (nodes[1].duons > 0)
        {
            create(nodes, 2, 6, nodes[1].duons);
            del(nodes, 1, 2);
        }

        // Вершина D
        del(nodes, 3, 2);
        del(nodes, 3, 7);
        if (nodes[3].duons > 0)
        {
            create(nodes, 6, 7, nodes[3].duons);
            del(nodes, 3, 7);
        }

        // Вершина E
        del(nodes, 4, 5);
        del(nodes, 4, 7);
        if (nodes[4].duons > 0)
        {
            create(nodes, 6, 7, nodes[4].duons);
            del(nodes, 4, 7);
        }

        // Вершина G
        del(nodes, 6, 2);
        del(nodes, 6, 5);
        del(nodes, 6, 7);
    }

    return 0;
}

void print_act(char first, char second, char act)
{
    cout << first << second << act << "\n";
}

void del(array<Node, MAX_N>& nodes, size_t first, size_t second)
{
    uint16_t min_duons = min(nodes[first].duons, nodes[second].duons);
    nodes[first].duons -= min_duons;
    nodes[second].duons -= min_duons;

    while (min_duons-- != 0)
        print_act(nodes[first].name, nodes[second].name, '-');
}

void create(array<Node, MAX_N>& nodes, size_t first, size_t second, uint16_t duons)
{
    nodes[first].duons += duons;
    nodes[second].duons += duons;

    while (duons-- != 0)
        print_act(nodes[first].name, nodes[second].name, '+');
}
