#include <iostream>
#include <stdint.h>
#include <array>

#define MAX_N 20 // Максимальное кол-во камней

using namespace std;

/**
 * @brief Расчет минимальной вохможной разницы веса двух кучек камней методом перебора
 * @param[in] w     Массив весов камней
 * @param[in] n     Кол-во камней
 * @param[in] w_tot Общий вес камней
 * @param[in] w_cur Текущий вес первой кучки
 * @return Минимальная разница веса двух кучек
*/
uint32_t min_diff(array<uint32_t, MAX_N>& w, size_t n, const uint32_t w_tot, uint32_t w_cur);

int main()
{
    size_t n = 0; // Кол-во камней
    cin >> n;

    array<uint32_t, MAX_N> w = {0};
    uint32_t w_total = 0; // Общий вес камней

    for(size_t i=0; i < n; i++)
    {
        cin >> w[i];
        w_total += w[i];
    }

    cout << min_diff(w, n, w_total, 0);

    return 0;
}

uint32_t min_diff(array<uint32_t, MAX_N>& w, size_t n, const uint32_t w_tot, uint32_t w_cur)
{
    if (n == 0 || w_cur >= w_tot/2) // Тривиальный исход - закончились камни или вес текущей кучки превысил половину общего веса
    {
        int32_t diff = w_tot - 2*w_cur;
        return abs(diff);
    }
    n--;
    return min(min_diff(w, n, w_tot, w_cur + w[n]), min_diff(w, n, w_tot, w_cur)); // Выбор минимального значения из кучки с текущим камнем и без него 
}