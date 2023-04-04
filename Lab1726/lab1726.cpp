#include <iostream>

using namespace std;

/**
 * @brief Реализация быстрой сортировки (рекурсивная)
 * @param[out] arr Указатель на массив
 * @param[in] l Крайний левый элемент
 * @param[in] r Крайний правый элемент
*/
void quickSort(uint32_t* arr, size_t l, size_t r);

int main()
{
    size_t n;
    cin >> n;

    uint32_t x[n];
    uint32_t y[n];

    for(size_t i=0; i < n; i++)
        cin >> x[i] >> y[i];

    // Сортируем в порядке возрастания
    quickSort(x, 0, n-1);
    quickSort(y, 0, n-1);

    // Считаем суммарную сумму всех путей
    uint64_t sum = 0;
    for(size_t i=1; i < n; i++)
        sum += 2*i*(n - i)*((x[i] - x[i-1]) + (y[i] - y[i-1]));
    
    cout << sum/n/(n-1);

    return 0;
}

void quickSort(uint32_t* arr, size_t l, size_t r)
{
    if (l < r)
    {
        uint32_t val = arr[(l + r)/2];
        size_t i = l, j = r;
        while (i <= j)
        {
            while (arr[i] < val) i++;
            while (arr[j] > val) j--;
            if (i >= j) break;
            uint32_t tmp = arr[i]; // Меняем местами элементы
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }

        quickSort(arr, l, j);
        quickSort(arr, j+1, r);
    }
}