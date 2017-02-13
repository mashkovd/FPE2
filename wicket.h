#ifndef WICKET_H
#define WICKET_H

#include <QPainter>
#include <QGraphicsItem>

class Wicket : public QGraphicsItem
{
public:
    Wicket();

    int myType;
    QRectF boundingRect() const
    {
        return QRectF(0, 0, 50, 50);
    }

    void setType(int Type);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

};

#endif // WICKET_H
