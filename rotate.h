#ifndef ROTATE_H
#define ROTATE_H

#include "ui_rotate.h"
#include <QGraphicsScene>
#include "qGraphicsViewCustom.h"

class Rotate : public QDialog, private Ui::Rotate
{
    Q_OBJECT

public:
    QPixmap pix;
    QGraphicsViewCustom *Frame;
    QGraphicsScene *scene;
    QTransform transform;
    int angle;

public:
    explicit Rotate(QWidget *parent = nullptr);
    void setInfo(QPixmap *p, QGraphicsScene *scene, QGraphicsViewCustom *Frame, int Angle);
    int getAngle();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_RotateSlider_valueChanged(int value);
};

#endif // ROTATE_H
