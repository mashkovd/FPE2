#include "wicket.h"

Wicket::Wicket()
{

}

void Wicket::setType(int Type)
{
    myType = Type;
}

void Wicket::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPen myPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    painter->setBrush(Qt::lightGray);
    painter->setPen(myPen);

    switch (myType) {
    case 0:
    {
        painter->drawRect(0, 0, 50, 50);
        painter->drawLine(25, 0, 25, 25);
        painter->drawLine(0, 50, 25, 25);
        painter->drawLine(50, 50, 25, 25);
    }
        break;
    case 1:
    {
        painter->drawRect(0, 0, 50, 50);
        painter->drawLine(0, 25, 50, 0);
        painter->drawLine(0, 25, 50, 50);
    }
        break;
    case 2:
    {
        painter->drawRect(0, 0, 50, 50);
        painter->drawEllipse(0, 0, 50, 25);
        painter->drawLine(25, 0, 25, 50);
    }
        break;
    }






}
