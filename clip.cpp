#include <QDebug>
#include "clip.h"

clip::clip(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(_lInput, SIGNAL(valueChanged(int)), this, SLOT(changeLargeur(int)));
    connect(_hInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
    connect(_x0Input, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
    connect(_y0Input, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
    connect(_xfInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
    connect(_yfInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
}
