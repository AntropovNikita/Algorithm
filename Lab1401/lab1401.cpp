#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;


/**
 * @brief Структура данных для доски
*/
typedef vector<vector<int32_t>> Board;

/**
 * @brief Отрисовка фигуры
 * @param[out] board Доска
 * @param[out] fig Номер фигуры
 * @param[in] x Левая координата квадрата по оси X
 * @param[in] y Верхняя координата квадрата по оси Y 
 * @param[in] px Координата окна по оси X
 * @param[in] py Координата окна по оси Y
 * @return true, если удалось отрисовать заданную фигуру, иначе false
*/
bool fill(Board& board, int32_t& fig, const size_t x, const size_t y, const size_t px, const size_t py);

/**
 * @brief Отрисовка фигуры в центре квадрата
 * @param[out] board Доска
 * @param[out] fig Номер фигуры
 * @param[in] x_cen Левая координата центра квадрата по оси X
 * @param[in] y_cen Верхняя координата центра квадрата по оси Y 
 * @param[in] px Координата окна по оси X
 * @param[in] py Координата окна по оси Y
 * @return true, если удалось отрисовать фигуру в центре, иначе false
*/
bool middle_fill(Board& board, int32_t& fig, const size_t x_cen, const size_t y_cen, const size_t px, const size_t py);

/**
 * @brief Заполнение доски фигурами
 * @param[out] board Доска
 * @param[out] fig Номер фигуры
 * @param[in] n Размер квадрата
 * @param[in] x Левая координата квадрата по оси X
 * @param[in] y Верхняя координата квадрата по оси Y 
 * @param[in] px Координата окна по оси X
 * @param[in] py Координата окна по оси Y
 * @return true, если удалось заполнить квадрат фигурами, иначе false
*/
bool make_board(Board& board, int32_t& fig, size_t n, size_t x, size_t y, size_t px, size_t py);

int main()
{
    size_t n, px, py;
    cin >> n >> px >> py;

    n = 1 << n; // Вычисление размера доски
    Board board(n, vector<int32_t>(n, -1));
    board[px-1][py-1] = 0; // Окно на доске
    int32_t fig = 1; // Номер первой фигуры

    if (make_board(board, fig, n, 0, 0, px-1, py-1)) // Если удалось заполнить доску, то отобразить ее
    {
        for(size_t i=0; i < n; i++)
        {
            for(size_t j=0; j < n; j++)
                cout << board[i][j] << " ";
            cout << "\n";
        }
    }
    else
        cout << -1;

    return 0;
}

bool fill(Board& board, int32_t& fig, const size_t x, const size_t y, const size_t px, const size_t py)
{
    uint16_t cell_fill = 0; // Кол-во ячеек для фигуры
    for(size_t i=0; i < 2; i++)
        for(size_t j=0; j < 2; j++)
            if (((x + i) != px || (y + j) != py) && board[x+i][y+j] == -1)
            {
                board[x+i][y+j] = fig;
                cell_fill++;
            }
    
    fig++; // Увеличение номера фигуры
    return cell_fill == 3;
}

bool middle_fill(Board& board, int32_t& fig, const size_t x_cen, const size_t y_cen, const size_t px, const size_t py)
{
    if (px <= x_cen)
    {
        if (py <= y_cen)
            return fill(board, fig, x_cen, y_cen, x_cen, y_cen);
        else
            return fill(board, fig, x_cen, y_cen, x_cen, y_cen+1);
    }
    else
    {
        if (py <= y_cen)
            return fill(board, fig, x_cen, y_cen, x_cen+1, y_cen);
        else
            return fill(board, fig, x_cen, y_cen, x_cen+1, y_cen+1);
    }
}

bool make_board(Board& board, int32_t& fig, size_t n, size_t x, size_t y, size_t px, size_t py)
{
    if (n == 2) // Тривиальный случай
        return fill(board, fig, x, y, px, py);

    n = n >> 1; // Половина от размера квадрата
    if (!middle_fill(board, fig, x+n-1, y+n-1, px, py)) // Заполнение центра квадрата
        return false;
    
    // Деление квадрата на 4 отдельных
    for (size_t i=0; i < 2; i++)
        for (size_t j=0; j < 2; j++) 
        {   
            if (x + i * n <= px && px < x + i * n + n && y + j * n <= py && py < y + j * n + n) 
            {
                // В квадрате есть окно
                if (!make_board(board, fig, n, x+i*n, y+j*n, px, py))
                    return false;
            } 
            else 
            {
                // В квадрате нет окна
                if (!make_board(board, fig, n, x+i*n, y+j*n, x+n-1+i, y+n-1+j))
                    return false;
            }
        }

    return true;
}