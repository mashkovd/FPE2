#ifndef PLANSSCENE_H
#define PLANSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

class PlansScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlansScene();

    int SceneW;
    int SceneH;

    int VertLineCount;
    int StepLine;

    qreal RadiusPoint;

    QPointF StartPoint;
    QPointF EndPoint;

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // PLANSSCENE_H
