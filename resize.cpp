
#include <QDebug>
#include "resize.h"

Resize::Resize(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(_lInput, SIGNAL(valueChanged(int)), this, SLOT(changeLargeur(int)));
    connect(_hInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
}

void Resize::setLargeur(int _largeur)
{
    largeur = _largeur;
    _lInput->setValue(largeur);
}
void Resize::setHauteur(int _hauteur)
{
    hauteur = _hauteur;
    _hInput->setValue(hauteur);
}

void Resize::changeLargeur(int l)
{
    if (_ratio->isChecked() && !ratio)
    {
        ratio = true;
        _hInput->setValue(l*_hInput->value()/largeur);
    }
    largeur = l;
    ratio = false;
}

void Resize::changeHauteur(int h)
{
    if (_ratio->isChecked() && !ratio)
    {
        ratio = true;
        _lInput->setValue(h*_lInput->value()/hauteur);
    }
    hauteur = h;
    ratio = false;
}
