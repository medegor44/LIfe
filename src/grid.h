/*
 * Сетка, на которой происходит действие игры
 */
#ifndef GRID
#define GRID

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QColor>
#include "LifeEngine/life.h"

class Grid : public QGraphicsObject
{
    Q_OBJECT

private:
    int w; // размеры поля в пикселах
    int h;
    int step; // размер 1 клтеки
    int **field;
    int counter; // счетчик поколений
    QColor color;
    Life *game;
    QTimer *timer;

public slots:
    void stopStartTimer();
    void runStep();
    void clear();
    void random();


signals:
    void counterChanged(int c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    Grid();
    Grid(int width, int height, int step);
    QRectF boundingRect() const
    { return QRectF(0, 0, w, h); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void loadConf(QString &path);
    int saveConf(QString &path);
    ~Grid();
};

#endif // GRID

