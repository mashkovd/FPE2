#include "plansscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

PlansScene::PlansScene()
{
    VertLineCount = 40;
    SceneH = 600;
    SceneW = 800;
    StepLine = round(SceneW/VertLineCount);

    RadiusPoint = StepLine/4;

//  Рисуем сетку с zValue = -1
    for (int i = 0; i <= VertLineCount; i++)
    {
        this->addLine(i * StepLine, 0, i * StepLine, SceneH, QPen(Qt::gray))->setZValue(-1);
    }

    for (int i = 0; i <= SceneH/StepLine; i++)
    {
        this->addLine(0, i * StepLine, SceneW, i * StepLine, QPen(Qt::gray))->setZValue(-1);
    }
}


void PlansScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void PlansScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (StartPoint != mouseEvent->scenePos())
    {
        StartPoint = mouseEvent->scenePos();


        addEllipse((round(StartPoint.QPointF::x()/StepLine)*StepLine - RadiusPoint),
                   (round(StartPoint.QPointF::y()/StepLine)*StepLine - RadiusPoint),
                   RadiusPoint * 2, RadiusPoint * 2, QPen(Qt::red));

        //addLine(StartPoint.x(), StartPoint.y(), EndPoint.x(), EndPoint.y(), QPen(Qt::black));
    }
    else
    {
        EndPoint = StartPoint;

        StartPoint = mouseEvent->scenePos();
        StartPoint.setX((round(StartPoint.QPointF::x()/StepLine)*StepLine - RadiusPoint));
        StartPoint.setY((round(StartPoint.QPointF::y()/StepLine)*StepLine - RadiusPoint));


    }

}

void PlansScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

