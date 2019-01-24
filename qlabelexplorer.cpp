#include "qlabelexplorer.h"
#include <qlabel.h>
#include <QMouseEvent>
#include <QDebug>

QLabelExplorer::QLabelExplorer(QWidget *parent):
    QLabel(parent)
{

}

void QLabelExplorer::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    qDebug() << "press !";
    emit mousePressed( p );
}

void QLabelExplorer::setUrlImage(QString img){
    URLimage = img;
}

QString QLabelExplorer::getUrlImage(){
    return URLimage;
}
