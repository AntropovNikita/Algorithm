#include <iostream>
#include <cmath>

#define MAX_ANGLE 90
#define MIN_ANGLE -90
#define PI 3.14159265358979323846

using namespace std;


/**
 * @brief Структура, описывающая точку
*/
struct Point
{
    uint16_t id;  ///< ID точки
    int64_t x;    ///< Координата по оси X
    int64_t y;    ///< Координата по оси Y
    double angle; ///< Угол прямой
};

/**
 * @brief Реализация быстрой сортировки (рекурсивная)
 * @param[out] arr Указатель на массив
 * @param[in] l Крайний левый элемент
 * @param[in] r Крайний правый элемент
*/
void quickSort(Point* arr, size_t l, size_t r);

int main()
{
    size_t n;
    cin >> n;

    Point points[n];

    size_t min_ind = 0; // Индекс крайнего левого элемента
    for(size_t i=0; i < n; i++)
    {
        cin >> points[i].x >> points[i].y;
        points[i].id = i + 1;
        if (i > 0 && (points[i].x < points[min_ind].x || // Условие выбора крайнего левого элемента
            (points[i].x == points[min_ind].x && points[i].y < points[min_ind].y)))
            min_ind = i;
    }
    Point tmp = points[min_ind]; //мПомещение крайней точки в начало массива
    points[min_ind] = points[0];
    points[0] = tmp;

    for(size_t i=1; i < n; i++) // Расчет углов
    {
        if (points[i].x == points[0].x) // При совпадении осей
        {
            if (points[i].y < points[0].y)
                points[i].angle = MIN_ANGLE;
            else
                points[i].angle = MAX_ANGLE;
        }
        else
            points[i].angle = atan((double)(points[i].y - points[0].y)/(points[i].x - points[0].x))*180.0/PI;
    }

    quickSort(points, 1, n-1);

    cout << points[0].id << " " << points[n/2].id;

    return 0;
}

void quickSort(Point* arr, size_t l, size_t r)
{
    if (l < r)
    {
        double val = arr[(l + r)/2].angle;
        size_t i = l, j = r;
        while (i <= j)
        {
            while (arr[i].angle < val) i++;
            while (arr[j].angle > val) j--;
            if (i >= j) break;
            Point tmp = arr[i]; // Меняем местами элементы
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }

        quickSort(arr, l, j);
        quickSort(arr, j+1, r);
    }
}