#include <iostream>
#include <cstring>
#include <vector>

using namespace std;


/**
 * @brief Получение индекса символа в алфавите
 * @param[in] c Символ
*/
int get_alh_index(char c);

/**
 * @brief Расчет вектора T для обратного BWT
 * @param[out] T Вектор T
 * @param[in] str Исходная строка
*/
void calc_T(vector<uint32_t>& T, string& str);

/**
 * @brief Обратное преобразование Берроуза-Вилера
 * @param[in] str Исходная строка
 * @param[in] pos Позиция последнего символа строки
*/
void backBWT(string& str, size_t pos);

int main()
{

    size_t n;
    string str;
    cin >> n >> str;
    n--;

    backBWT(str, n);

    return 0;
}

int get_alh_index(char c)
{
    if(c >= 'A' && c <= 'Z') 
        return c-'A';
    if(c == '_') 
        return 26;
    return c-'a'+27;
}

void calc_T(vector<uint32_t>& T, string& str)
{
    constexpr size_t alh_n = strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz"); // Задание длины алфавита
    vector<uint32_t> D(alh_n+1, 0); // Массив кол-ва символов до i-го в алфавитном порядке
    
    for(size_t i=0; i < str.size(); i++) // Расчет C(alh) - массива частоты i-го символа. Сдвиг на 1 нужен для расчета D(alh)
        D[get_alh_index(str[i])+1]++;

    for(size_t i=1; i < D.size(); i++) // Расчет D(alh)
        D[i] += D[i-1];

    for(size_t i=0; i < str.size(); i++) // Расчет T с инверсией для вывода с первого символа, а не последнего
        T[D[get_alh_index(str[i])]++] = i;
}

void backBWT(string& str, size_t pos)
{
    vector<uint32_t> T(str.size(), 0);
    calc_T(T, str);

    for(size_t i=0; i < str.size(); i++)
    {
        pos = T[pos]; // Индекс следующего символа
        cout << str[pos];
    }
}