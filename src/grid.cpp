#include "grid.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>

Grid::Grid(int width, int height, int step)
{
    w = width;
    h = height;
    this->step = step;

    counter = 0;

    field = NULL; // "Игровое" поле

    timer = new QTimer(); // таймер

    game = new Life(w/step, h/step); /* кол-во клеток = размер в пикселах /
                                        на кол-во пикселей в 1 клетке */

    connect(timer, SIGNAL(timeout()), this, SLOT(runStep()));
    // при истечении времени на таймере происходит совершение 1 итерации игры
    connect(timer, SIGNAL(timeout()), timer, SLOT(start()));
    // и запуск таймера заново
}

void Grid::runStep()
{
    game->run(); // совершение 1 итерации игры
    counter++;
    emit counterChanged(counter);
    update(); // обновить
}

void Grid::stopStartTimer()
// остановка/запуск таймера
{
    if(!timer->isActive()) timer->start(10);
    else timer->stop();
}

void Grid::clear()
{
    timer->stop(); // остановить таймер
    game->clear(); // очистить поле в классе алгоритма
    counter = 0; // сбросить счетчик
    emit counterChanged(counter); // сообщить о его изменении
    update(); // перерисовать поле
}

void Grid::random()
{
    timer->stop(); // остановить таймер
    game->random();
    counter = 0; // сбросить счетчик
    emit counterChanged(counter); // сообщить о его изменении
    update(); // перерисовать поле
}

int Grid::saveConf(QString &path)
{
    QFile file(path);

    qDebug() << path;

    if(!(file.open(QFile::WriteOnly | QFile::Text)))
    { qDebug() << "Can't open file!"; return 0; }

    qDebug() << "Success!";

    qDebug() << file.isOpen();

    int **savingConf = game->getField();
    QTextStream in(&file);


    in << w << '\n' << h << '\n';

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            in << savingConf[i][j] << ' ';
        in << '\n';
    }

    return 1;
}

void Grid::loadConf(QString &path)
{
    game->loadFromFile(path);
    update();
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget)
// отрисовка игрового поля
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    field = game->getField();

    for(int i = 0; i <= w; i += step)
        painter->drawLine(i, 0, i, h);
    for(int i = 0; i <= h; i += step)
        painter->drawLine(0, i, w, i);

    for(int i = 0; i < h; i += step)
        for(int j = 0; j < w; j += step)
            if(field[i/step][j/step]) //если клетка жива - отобразить ее
                painter->fillRect(QRectF(j+1, i+1, step-1, step-1), Qt::blue);
}

void Grid::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int a = (event->pos()).x() / step;
    int b = (event->pos()).y() / step;

    game->setCell(b, a); // установка живой клетки

    update(); // обновление поля
}

Grid::~Grid()
{
    delete timer;
}
