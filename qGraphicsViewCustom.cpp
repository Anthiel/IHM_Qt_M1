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
    qDebug() << "PRESS" << ev->x() << ev->y();
    Xbegin = ev->x(), Ybegin = ev->y();
    emit mousePressed( p );    
}

void QGraphicsViewCustom::mouseMoveEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    qDebug() << "MOVE" << ev->x() << ev->y();
    Xend = ev->x(), Yend = ev->y();
    emit mousePressed( p );

}

void QGraphicsViewCustom::mouseReleaseEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    qDebug() << "RELEASE" << ev->x() << ev->y();
     Xend = ev->x(), Yend = ev->y();
    emit mousePressed( p );
}


void QGraphicsViewCustom::setID(int i){
    ID = i;
}

int QGraphicsViewCustom::getID(){
    return ID;
}
