#include "life.h"
#include <QDebug>

Life::Life(int w, int h)
{
    this->w = w;
    this->h = h;

    allocateMemory(); // выделение памяти
}
void Life::allocateMemory()
{
    IO = new int* [h];
    Processing = new int* [h];

    for(int i = 0; i < h; i++) {
        IO[i] = new int[w];
        Processing[i] = new int[w];
    }

    init(IO);
    init(Processing);
}
void Life::init(int **m)
{
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            m[i][j] = 0;
}

int Life::defineCount(int i, int j)
{
    int count = 0;
    int tmpI = i-1 < 0 ? h-1 : i-1;
    int tmpJ = j-1 < 0 ? w-1 : j-1;

    for(int a = 0; a < 3; a++) {
        for(int b = 0; b < 3; b++) {
            if(Processing[tmpI][tmpJ])
                count++;
            tmpJ++;
            if(tmpJ == w)
                tmpJ = 0;
        }
        tmpJ = j-1 < 0 ? w-1 : j-1;
        tmpI++;
        if(tmpI == h)
            tmpI = 0;
    }

    return Processing[i][j] ? count-1 : count;
}
void Life::copy()
{
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            Processing[i][j] = IO[i][j];
}
void Life::random()
{
    init(IO);

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            int a = rand() % 10;
            int b = rand() % 10;
            
            b &= a;
            a &= b;
            
            IO[i][j] = a % 2;
        }
}
void Life::run()
{
    copy();

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++) {
            if(Processing[i][j] == 1) {
                int count = defineCount(i, j);
                if(count != 3 && count != 2)
                        IO[i][j] = 0;
            } else {
                if(defineCount(i, j) == 3)
                    IO[i][j] = 1;
            }
        }

    init(Processing);
}
void Life::loadFromFile(QString &path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    { qDebug() << "Can't open file"; return; }

    QTextStream out(&file);
    int width, height; // размеры фигуры
    out >> width; out >> height;

    if(width <= w && height <= h) {
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                out >> IO[i][j];
    } else qDebug() << "Config is too big";
}
void Life::setCell(int i, int j)
{
    if(i < h && j < w)
        IO[i][j] = IO[i][j] ? 0 : 1;
}
Life::~Life()
{
    for(int i = 0; i < h; i++) {
        delete [] IO[i];
        delete [] Processing[i];
    }

    delete IO;
    delete Processing;
}
