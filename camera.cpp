#include "camera.h"
#include <QPen>

Camera::Camera()
{

}
void Camera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen myPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    //myPen.setColor(Qt::red);
    painter->setBrush(Qt::lightGray);
    painter->setPen(myPen);

    QPointF pointsTriangle[3] = {
        QPointF( 0, 5),
        QPointF(20, 25),
        QPointF( 0, 45),
    };

    painter->drawPolygon(pointsTriangle, 3,Qt::WindingFill);

    QPointF pointsRect[4] = {
        QPointF( 15, 10),
        QPointF( 15, 40),
        QPointF(55, 40),
        QPointF(55, 10),
    };

    painter->drawPolygon(pointsRect, 4);


    //QLineF *myLine = new QLineF(1,1,100,100);
    //QVector <QLineF> myVector;
    //myVector.append(QLineF(100, 100, 200, 100));
    //myVector.append(QLineF(0, 0, 100, 100));


    //painter->drawLines(myVector);
    //painter->drawLine(50,0,100,50);
    //painter->drawLine(100, 25 , 200, 25);

}



