#include <iostream>

using namespace std;

/**
 * @brief Структура, описывающая знак
*/
struct Sign
{
    uint16_t id;    ///< ID знака
    uint16_t count; ///< Кол-во знаков
};

int main()
{
    size_t k; // Кол-во типов знаков
    cin >> k;

    Sign signs[k];
    uint16_t all_sign = 0; // Кол-во знаков
    uint16_t min_val = UINT16_MAX;
    uint16_t max_val = 0;
    uint16_t min_ind, max_ind;
    for(size_t i=0; i < k; i++)
    {
        cin >> signs[i].count;
        signs[i].id = i + 1;
        if (signs[i].count >= max_val) // Поиск максимального кол-ва знаков
        {
            max_val = signs[i].count;
            max_ind = i;
        }
        if (signs[i].count < min_val && i != min_ind) // Поиск минимального кол-ва знаков
        {
            min_val = signs[i].count;
            min_ind = i;
        }

        all_sign += signs[i].count;
    }

    while (all_sign > 0)
    {
        if (signs[max_ind].count > 0) // Вывод знака с максимальным кол-вом
        {
            cout << signs[max_ind].id << " ";
            signs[max_ind].count--;
            all_sign--;
        }

        if (signs[min_ind].count > 0) // Вывод знака с минимальным кол-вом
        {
            cout << signs[min_ind].id << " ";
            signs[min_ind].count--;
            all_sign--;
        }

        max_val = 0;
        min_val = UINT16_MAX;
        for(size_t i=0; i < k; i++) // Поис минимального и максимального знаков
            if (signs[i].count > 0)
            {
                if (signs[i].count >= max_val)
                {
                    max_val = signs[i].count;
                    max_ind = i;
                }
                if (signs[i].count < min_val)
                {
                    min_val = signs[i].count;
                    min_ind = i;
                }
            }
    }

    return 0;
}
