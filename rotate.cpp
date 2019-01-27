#include <QDebug>
#include "rotate.h"

Rotate::Rotate(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}


void Rotate::changeAngle()
{

}



void Rotate::on_buttonBox_accepted()
{
    qDebug() << "accepted";
}

void Rotate::on_buttonBox_rejected()
{
    qDebug() << "rejeted";
}
