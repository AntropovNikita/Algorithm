#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846
#define EPS 1e-10 // Константа для сравнения примерно равных чисел с плавающей запятой

using namespace std;

/**
 * @brief Структура, описывающая тыквы
*/
struct Pumpkin
{
    uint16_t id;  ///< ID тыквы
    uint32_t len; ///< Расстояние до тыквы
    double angle; ///< Угол между осью X и прямой до тыквы

    /**
     * @brief Сравнение тыкв
     * @param[in] other Другая тыква
     * @return true, если тыква меньше другой, иначе false
    */
    bool lessThenPump(const Pumpkin& other)
    {
        if (abs(angle - other.angle) > EPS) // Для тыкв на разных прямых
            return angle < other.angle;
        
        return len < other.len; // Для тыкв на одной прямой
    }
};

/**
 * @brief Реализация быстрой сортировки (рекурсивная)
 * @param[out] arr Указатель на массив
 * @param[in] l Крайний левый элемент
 * @param[in] r Крайний правый элемент
*/
void quickSort(Pumpkin* arr, size_t l, size_t r);

int main()
{
    size_t N;
    cin >> N;

    Pumpkin pump[--N];
    int16_t x0, y0; // Стартовая тыква
    cin >> x0 >> y0;
    for(size_t i=0; i < N; i++)
    {
        int16_t x, y;
        cin >> x >> y;
        
        pump[i].angle = atan2(y - y0, x - x0);
        pump[i].len = pow((x - x0), 2) + pow((y - y0), 2); // Расстояние в квадрате для упрощения сравнений и уменьшения кол-ва вычислений
        pump[i].id = i + 2;
    }

    quickSort(pump, 0, N-1);

    double max_diff = 2*PI - (pump[N-1].angle - pump[0].angle); // Разница против часовой стрелки между минимальным и максимальным углами
    size_t k = 0;
    for(size_t i=1; i < N; i++)
    {
        if (pump[i].angle - pump[i-1].angle > max_diff) // Поиск точки перехода между (если разница между соседними углами больше заданной)
        {
            k = i;
            max_diff = pump[i].angle - pump[i-1].angle;
        }
    }

    cout << N+1 << "\n";
    cout << "1\n";
    for(size_t i=k; i < N; i++) // Вывод тыкв до перехода
        cout << pump[i].id << "\n";
    for(size_t i=0; i < k; i++) // Вывод тыкв после перехода
        cout << pump[i].id << "\n";

    return 0;
}

void quickSort(Pumpkin* arr, size_t l, size_t r)
{
    if (l < r)
    {
        Pumpkin val = arr[(l + r)/2];
        size_t i = l, j = r;
        while (i <= j)
        {
            while (arr[i].lessThenPump(val)) i++;
            while (val.lessThenPump(arr[j])) j--;
            if (i >= j) break;
            Pumpkin tmp = arr[i]; // Меняем местами элементы
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }

        quickSort(arr, l, j);
        quickSort(arr, j+1, r);
    }
}