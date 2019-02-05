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
    const QPointF f = mapToScene (p);
    //qDebug() << "PRESS" << ev->x() << ev->y() << "mapToScene :" << f.x() << f.y();
    if(!SelectCreer){   // si la selection n'a pas été créée
        Xbegin = f.x(), Ybegin = f.y();
        Xend = f.x(), Yend = f.y();
    }

    emit mousePressed( p );    
}

void QGraphicsViewCustom::mouseMoveEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    const QPointF f = mapToScene (p);
    //qDebug() << "MOVE" << ev->x() << ev->y()<< "mapToScene :" << f.x() << f.y();
    x1 = f.x(), y1 = f.y();

    if(!SelectCreer)
        Xend = f.x(), Yend = f.y();
    emit mousePressed( p );

}

void QGraphicsViewCustom::mouseReleaseEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    const QPointF f = mapToScene (p);
    //qDebug() << "RELEASE" << ev->x() << ev->y() << "mapToScene :" << f.x() << f.y();
    if(!SelectCreer)
        Xend = f.x(), Yend = f.y();

    SelectCreer = true;
    emit mousePressed( p );
}


void QGraphicsViewCustom::setID(int i){
    ID = i;
}

int QGraphicsViewCustom::getID(){
    return ID;
}
