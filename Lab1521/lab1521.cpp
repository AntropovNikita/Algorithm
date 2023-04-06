#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;


/**
 * @brief Перечисление направления обхода дерева
*/
enum MoveDir 
{ 
    FROM_LEFT_CHILD,  ///< От левого потомка к родителю 
    FROM_RIGHT_CHILD, ///< От правого потомка к родителю
    FROM_PARENT       ///< От родителя к потомку
};

/**
 * @brief Структура данных для описания дерева отрезков
*/
struct Tree
{
    vector<uint32_t> val; ///< Массив значений вершин дерева
    size_t el_num;        ///< Кол-во элементов множества, по которому строится дерево
    size_t leaf_ind;      ///< Индекс крайнего левого листа дерева

    /**
     * @brief Конструктор структуры
     * 
     * @param[in] n Кол-во элементов множества
    */
    Tree(size_t n)
    {
        this->el_num = n--;
        for (size_t p=1; p<32; p<<=1) // Поиcк ближайшей сверху степени 2
            n |= (n >> p);

        this->leaf_ind = n + 1;
        this->val.resize(this->leaf_ind*2, 0);
        for(size_t i=0; i < this->el_num; i++) // Заполнение значений для листов дерева
            val[this->leaf_ind + i] = 1;

        for(size_t i = this->leaf_ind-1; i > 0; i--) // Заполнение оставшихся вершин
            val[i] = val[this->left(i)] + val[this->right(i)];
    }

    /**
     * @brief Получение индекса левого потомка
     * 
     * @param[in] parent Индекс родителя
     * @return Индекс потомка
    */
    size_t left(const size_t& parent) { return 2*parent; }

    /**
     * @brief Получение индекса правого потомка
     * 
     * @param[in] parent Индекс родителя
     * @return Индекс потомка
    */
    size_t right(const size_t& parent) { return 2*parent + 1; }

    /**
     * @brief Получение индекса родителя
     * 
     * @param[in] child Индекс потомка
     * @return Индекс родителя
    */
    size_t parent(const size_t& child) { return child/2; }

    /**
     * @brief Проверка, принадлежит ли вершина дереву (в диапазон (0; индекс первого листа + кол-во элементов множества))
     * 
     * @param[in] node Индекс вершины
     * @return true, если принадлежит, иначе false
    */
    bool is_node(const size_t& node) { return (node < this->leaf_ind + this->el_num) && node > 0; }
};

/**
 * @brief Вывод номеров солдат в нужном порядке
 * 
 * @param[out] tree Указатель на дерево отрезков
 * @param[in] k Шаг для вывода солдат
*/
void querySoldiers(Tree* tree, size_t k);

int main()
{
    size_t n, k;
    cin >> n >> k;

    Tree tree(n);

    querySoldiers(&tree, k);

    return 0;
}

void querySoldiers(Tree* tree, size_t k)
{
    size_t el_remain = tree->el_num; // Кол-во оставшихся элементов множества
    size_t next = k; // Номер следующего элемента множества

    while (el_remain)
    {
        if (el_remain-- == tree->el_num) // Если еще ни одного элемента множества не удалено
        {
            cout << next << " ";
            continue;
        }

        size_t prev = tree->leaf_ind - 1 + next; // Расчет индекса вершины, соотвествующего удаленному элементу множества
        while (prev) // Перерасчет значений вершин дерева
        {
            tree->val[prev]--;
            prev = tree->parent(prev);
        }

        prev = tree->leaf_ind - 1 + next;
        size_t step = k; // Шаг поиска от предыдущего элемента множества
        MoveDir move_dir = FROM_RIGHT_CHILD; // Направление обхода дерева начальное
        
        while(step)
        {
            size_t left = tree->left(prev);
            size_t right = tree->right(prev);

            if(move_dir == FROM_PARENT) // Если переходим от родителя к потомку
            {
                if(tree->is_node(left) && step > tree->val[left]) // Если есть левый потомок и кол-во элементов в нем меньше, чем шаг
                {
                    step -= tree->val[left]; // Сокращаем шаг и переходим к правому потомку
                    move_dir = FROM_PARENT;
                    prev = right;
                }
                else if(!tree->is_node(left) && step == tree->val[prev]) // Если находимся в листе
                    step--; // Сокращаем шаг
                else // Иначе переходим к левому потомку
                {
                    move_dir = FROM_PARENT;
                    prev = left;
                }
            }
            else if(move_dir == FROM_RIGHT_CHILD) // Если переходим от правого потомка к родителю
            {
                move_dir = (prev == tree->right(tree->parent(prev))) ? FROM_RIGHT_CHILD : FROM_LEFT_CHILD; // Проверяем направление перехода
                prev = tree->parent(prev); // Переходи к родителю
            }
            else // Если переходим от левого потомка к родителю
            {
                if(tree->is_node(right) && step > tree->val[right]) // Если есть правый потомок и кол-во элементов в нем меньше, чем шаг
                {
                    move_dir = (prev == tree->right(tree->parent(prev))) ? FROM_RIGHT_CHILD : FROM_LEFT_CHILD; // Проверяем направление перехода
                    prev = tree->parent(prev); // Переходим к родителю
                    step -= tree->val[right]; // Сокращаем шаг
                }
                else // Иначе переходим к правому потомку
                {
                    prev = right;
                    move_dir = FROM_PARENT;
                }
            }
            if(!tree->is_node(prev))
            {           
                prev = tree->leaf_ind;
                step -= tree->val[prev];
                move_dir = FROM_RIGHT_CHILD;
            }
        }

        next = prev + 1 - tree->leaf_ind;
        cout << next << " ";
    }
}