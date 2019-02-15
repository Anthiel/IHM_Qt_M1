#ifndef ROTATE_H
#define ROTATE_H

#include "ui_rotate.h"
#include <QGraphicsScene>
#include "qGraphicsViewCustom.h"
#include "QGraphicsSceneCustom.h"

class Rotate : public QDialog, private Ui::Rotate
{
    Q_OBJECT

public:
    QPixmap *pix;
    QGraphicsViewCustom *Frame;
    QGraphicsSceneCustom *scene;

    QPixmap *pixExp;
    QGraphicsViewCustom *FrameExp;
    QGraphicsSceneCustom *sceneExp;

    QPixmap *pixCM;
    QGraphicsViewCustom *FrameCM;
    QGraphicsSceneCustom *sceneCM;

    QTransform transform;
    int angle = 0;
    int nouveauAngle;
    std::vector <int> SelectionMultiple;

public:
    explicit Rotate(QWidget *parent = nullptr);
    void setInfo(QPixmap *p, QGraphicsSceneCustom *scene, QGraphicsViewCustom *Frame,  std::vector <int> SelectionMultiple,
                 QPixmap *pExp, QGraphicsSceneCustom *sceneExp, QGraphicsViewCustom *FrameExp,
                 QPixmap *pCarteM, QGraphicsSceneCustom *sceneCarteM, QGraphicsViewCustom *FrameCarteM);
    int getAngle();


private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_RotateSlider_valueChanged(int value);
};

#endif // ROTATE_H
