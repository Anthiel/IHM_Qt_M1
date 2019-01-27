#include "qGraphicsViewCustom.h"
#include <QMouseEvent>
#include <QDebug>

QGraphicsViewCustom::QGraphicsViewCustom(QWidget *parent):
    QGraphicsView(parent)
{

}

void QGraphicsViewCustom::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    qDebug() << "press !";
    qDebug() << ev->x() << ev->y();
    emit mousePressed( p );
}

void QGraphicsViewCustom::setID(int i){
    ID = i;
}

int QGraphicsViewCustom::getID(){
    return ID;
}
