#include <iostream>
#include <map>
#include <sstream>
#include <stdint.h>

using namespace std;

/**
 * @brief Узел дерева
*/
struct Tree
{
    /**
     * @brief Констурктор узла дерева
    */
    Tree() { this->children = {}; }

    map< string, Tree*> children; /** Потомки узла */
};

/**
 * @brief Добавление вложенных папок в дерево
 * @param[out] root Указатель на корень дерева
 * @param[in] path Пусть с вложенными папками
*/
void add_path(Tree* root, string path);

/**
 * @brief Обход и вывод дерева
 * @param[in] cur_tree Текущий узел
 * @param[in] depth Глубина узла
*/
void print_tree(Tree* cur_tree, uint16_t depth);

int main()
{
    size_t n;
    cin >> n;

    Tree* root = new Tree(); // Корень дерева

    string path;
    for(size_t i=0; i < n; i++)
    {
        cin >> path;
        add_path(root, path);
    }

    print_tree(root, 0);

    return 0;
}

void add_path(Tree* root, string path)
{
    stringstream stream(path);
    string dir;

    Tree* cur_dir = root;
    while (getline(stream, dir, '\\'))
    {
        auto node = cur_dir->children.insert({dir, new Tree()});
        cur_dir = node.first->second;
    }
}

void print_tree(Tree* cur_tree, uint16_t depth) 
{

    for(auto dir : cur_tree->children)
    {
        cout << string(depth, ' ') << dir.first << "\n";
        print_tree(dir.second, depth+1);
    }
}