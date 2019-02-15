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

void Rotate::setInfo(QPixmap *p, QGraphicsSceneCustom *scene, QGraphicsViewCustom *Frame,  std::vector <int> SelectionMultiple,
                     QPixmap *pExp, QGraphicsSceneCustom *sceneExp, QGraphicsViewCustom *FrameExp,
                     QPixmap *pCarteM, QGraphicsSceneCustom *sceneCarteM, QGraphicsViewCustom *FrameCarteM){
    pix = p;
    this->Frame = Frame;
    this->scene = scene;

    pixExp = pExp;
    this->FrameExp = FrameExp;
    this->sceneExp = sceneExp;

    pixCM = pCarteM;
    this->FrameCM = FrameCarteM;
    this->sceneCM = sceneCarteM;

    this->SelectionMultiple = SelectionMultiple;
}


void Rotate::on_buttonBox_accepted()
{
    angle = RotateSlider->value();
    for(int k = 0; k < SelectionMultiple.size(); k++){
        int i = SelectionMultiple.at(k);
        QTransform transform;
        nouveauAngle = (angle + scene[i].getAngle())%360;
        transform.rotate(nouveauAngle);
        scene[i].setAngle(nouveauAngle);
        pix[i] = pix[i].transformed(transform);
        scene[i].clear();
        scene[i].addPixmap(pix[i]);
        scene[i].setSceneRect(pix[i].rect());
        Frame->fitInView(scene[i].sceneRect(),Qt::KeepAspectRatio);

        sceneExp[i].setAngle(nouveauAngle);
        pixExp[i] = pixExp[i].transformed(transform);
        sceneExp[i].clear();
        sceneExp[i].addPixmap(pixExp[i]);
        sceneExp[i].setSceneRect(pixExp[i].rect());

        sceneCM[i].setAngle(nouveauAngle);
        pixCM[i] = pixCM[i].transformed(transform);
        sceneCM[i].clear();
        sceneCM[i].addPixmap(pixCM[i]);
        sceneCM[i].setSceneRect(pixCM[i].rect());
        FrameCM->fitInView(sceneCM[i].sceneRect(),Qt::KeepAspectRatio);
    }
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
