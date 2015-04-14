/*
 * Основной алгоритм игры
 */
#ifndef LIFE_H
#define LIFE_H

#include <QTextStream>
#include <QFile>

class Life
{
private:
    int **IO; // матрица ввода-вывода
    int **Processing; // обрабатывающая
    int h; // высота поля
    int w; // ширина поля

    void allocateMemory(); // выделение памяти под матрицы
    void init(int **m);
    void writeFile();
    void copy();
    int defineCount(int i, int j); // определение оличества соседей у клетки

public:
    Life(int w, int h);

    void run(); // запуск 1 шага игры
    void random(); // установка счлучайных значений на поле
    void setCell(int i, int j); // установка клетка на поле
    void loadFromFile(QString &path);
    inline int **getField() // получение текущего поля
    { return IO; }

    inline void clear() // очистка поля
    { init(IO); }

    ~Life();
};

#endif // LIFE_H
