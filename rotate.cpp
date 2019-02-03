#include <QDebug>
#include "rotate.h"
#include <QGraphicsScene>
#include "qGraphicsViewCustom.h"
#include "QGraphicsSceneCustom.h"

Rotate::Rotate(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void Rotate::setInfo(QPixmap *p, QGraphicsSceneCustom *scene, QGraphicsViewCustom *Frame){
    pix = *p;
    this->Frame = Frame;
    this->scene = scene;
}


void Rotate::on_buttonBox_accepted()
{
    angle = RotateSlider->value();

    QTransform transform;
    nouveauAngle = (angle + scene->getAngle())%360;
    transform.rotate(nouveauAngle);
    scene->setAngle(nouveauAngle);
    pix = pix.transformed(transform);
    scene->clear();
    scene->addPixmap(pix);
    scene->setSceneRect(pix.rect());
    Frame->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}


int Rotate::getAngle(){
    return nouveauAngle;
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
