#ifndef CELL
#define CELL

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Cell : public QGraphicsItem
{
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // CELL

