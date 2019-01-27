#include <QDebug>
#include "rotate.h"
#include <QGraphicsScene>
#include "QGraphicsViewCustom.h"

Rotate::Rotate(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void Rotate::setInfo(QPixmap *p, QGraphicsScene *scene, QGraphicsViewCustom *Frame, int Angle){
    pix = *p;
    this->Frame = Frame;
    this->scene = scene;
    this->angle = Angle;
    RotateSlider->setValue(angle);
    _hInput->setValue(angle);
}


void Rotate::on_buttonBox_accepted()
{
    qDebug() << "accepted" << angle;
    QTransform transform;
    transform.rotate(angle);
    pix = pix.transformed(transform);
    scene->clear();
    scene->addPixmap(pix);
    scene->setSceneRect(pix.rect());
    Frame->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

int Rotate::getAngle(){
    return angle;
}

void Rotate::on_buttonBox_rejected()
{
    qDebug() << "rejeted";
}

void Rotate::on_RotateSlider_valueChanged(int value)
{
    angle = value;
    qDebug() << "changement de valeur" << angle;
}
