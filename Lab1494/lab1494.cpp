#include <iostream>
#include <stack>
#include <stdint.h>

using namespace std;

/**
 * @brief Проверка последовательности шаров
 * @param[in] balls Стек с правильным порядком шаров
 * @param[in] n  Кол-во шаров
 * @return true, если порядок неправильный, иначе false
*/
bool check_cheat(stack<uint32_t>& balls, size_t n);

int main()
{
    size_t n;
    cin >> n;

    stack<uint32_t> balls;

    if (check_cheat(balls, n))
        cout << "Cheater";
    else
        cout << "Not a proof"; 
}

bool check_cheat(stack<uint32_t>& balls, size_t n)
{
    uint32_t cur_ball; // Текущий шар
    uint32_t max_num = 0; // Текущее максимальное значение

    for(size_t i=0; i < n; i++)
    {
        cin >> cur_ball;

        if (cur_ball > max_num) // Заполняем разницу между последним максимальным значением и текущим шаром в правильном порядке
        {
            for(uint32_t j=max_num+1; j < cur_ball; j++)
                balls.push(j);
            max_num = cur_ball;
        }
        else if (cur_ball == balls.top()) // Проверка шаров на порядок следования
            balls.pop();
        else
            return true;
    }

    return !balls.empty(); // Проверка, остались ли еще неосмотренные шары в стеке
}