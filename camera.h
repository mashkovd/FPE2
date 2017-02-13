#ifndef CAMERA_H
#define CAMERA_H

#include <QGraphicsItem>
#include <QPainter>

class Camera : public QGraphicsItem
{

public:
    Camera();

    QRectF boundingRect() const
    {
        return QRectF(0, 0, 60, 50);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

};

#endif // CAMERA_H
