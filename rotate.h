#ifndef ROTATE_H
#define ROTATE_H

#include "ui_rotate.h"

class Rotate : public QDialog, private Ui::Rotate
{
    Q_OBJECT


public:
    explicit Rotate(QWidget *parent = nullptr);

private slots:
    void changeAngle();

    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // ROTATE_H
