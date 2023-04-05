#include <iostream>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

/**
 * @brief Структура, описывающая миллиардеров
*/
struct Person
{
    string city;    ///< Текущее местоположением
    uint64_t money; ///< Состояние
};

/**
 * @brief Структура, описывающая всех миллиардеров
*/
struct Persons
{
    unordered_map<string, Person> info; ///< Информация о всех миллиардерах

    /**
     * @brief Добавление нового миллиардера в структуру
     * @param[in] name Фамилия миллиардера
     * @param[in] city Текущий город расположения
     * @param[in] money Состояние
    */
    void addPerson(string name, string city, uint64_t money) { info[name] = {city, money}; }
};

/**
 * @brief Структура, описывающая информацию о городах
*/
struct Cities
{
    unordered_map<string, uint64_t> capitals;      ///< Информация о капитализации городов
    map<uint64_t, set<string>, greater<>> leaders; ///< Информация о городах с максимальной капитализацией
    map<string, uint16_t> top;                     ///< Топ городов по кол-ву дней с максимальной капитализацией

    /**
     * @brief Изменение капитализации города
     * @param[in] city Название города
     * @param[in] money Изменение капитализации
     * @param[in] add Знак изменения капитализации
    */
    void addMoney(string city, uint64_t money, bool add) 
    {   
        auto capital = capitals.find(city);
        if (capital != capitals.end()) // Если город уже обрабатывался
        {
            if (capital->second != 0)
            {
                auto leader = leaders.find(capital->second); // Удаление из множества городов 
                leader->second.erase(city);                  // с текущей капитализацией
                if (leader->second.size() == 0) leaders.erase(leader);
            }

            if (add) // Изменение капитализации
                capital->second += money;
            else
                capital->second -= money;
            money = capital->second;
        }
        else // Добавление города в структуру
            capitals[city] = money; 

        if (money > 0)
            leaders[money].insert(city); // Добавление города в множество городов с новой капитализацией
    }

    /**
     * @brief Обновление топа городов
     * @param[in] days Кол-во прошедших дней
    */
    void refreshTop(uint16_t days)
    {
        if (leaders.begin()->second.size() == 1 && days > 0) // Если в множестве городов только один город
        {
            for(auto city : leaders.begin()->second)
            {
                auto cur_city = top.find(city);
                if (cur_city != top.end()) // Если город уже есть в топе
                    cur_city->second += days;
                else
                    top[city] = days;
            }
        }
    }
};

int main()
{
    size_t n;
    cin >> n;

    Persons persons;
    Cities cities;
    for(size_t i=0; i < n; i++) // Ввод информации о миллиардерах
    {
        string name, city;
        uint64_t money;
        cin >> name >> city >> money;

        persons.addPerson(name, city, money);
        cities.addMoney(city, money, true);
    }

    uint16_t m; // Общее кол-во дней
    size_t k;
    cin >> m >> k;
    uint16_t prev_day = 0;
    for(size_t i=0; i < k; i++)
    {
        uint16_t day;
        string name, new_city;
        cin >> day >> name >> new_city;

        cities.refreshTop(day - prev_day);

        auto person = persons.info.find(name); // Изменение капитализации и топа городов
        cities.addMoney(person->second.city, person->second.money, false); // Текущего города
        cities.addMoney(new_city, person->second.money, true); // Нового города
        person->second.city = new_city;

        prev_day = day;
    }

    cities.refreshTop(m - prev_day);

    for(auto city : cities.top)
        cout << city.first << " " << city.second << "\n";

    return 0;
}
