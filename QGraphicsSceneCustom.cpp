#include "QGraphicsSceneCustom.h"
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>



QGraphicsSceneCustom::QGraphicsSceneCustom()
{
    //qDebug() << "création de la scène";
}


int QGraphicsSceneCustom::getAngle(){
    return angle;
}

void QGraphicsSceneCustom::setAngle(int a){
    angle = a;
}

void QGraphicsSceneCustom::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    const QPointF p = ev->scenePos();
    //qDebug() << "SCENE :" << ev->scenePos().x();
    this->update();
}

void QGraphicsSceneCustom::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    const QPointF p = ev->scenePos();
    //qDebug() << "SCENE :" << ev->scenePos().x();
    this->update();
}

void QGraphicsSceneCustom::mouseMoveEvent(QGraphicsSceneMouseEvent *ev)
{
    const QPointF p = ev->scenePos();
    //qDebug() << "SCENE :" << ev->scenePos().x();
    this->update();
}
