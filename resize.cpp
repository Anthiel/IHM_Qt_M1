
#include <QDebug>
#include "resize.h"

Resize::Resize(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(_lInput, SIGNAL(editingFinished()), this, SLOT(changeLargeur()));
    connect(_hInput, SIGNAL(editingFinished()), this, SLOT(changeHauteur()));
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

void Resize::changeLargeur()
{
    int l = _lInput->value();
    if (_ratio->isChecked() && !ratio)
    {
        ratio = true;
        _hInput->setValue(l*_hInput->value()/largeur);
    }
    else if (ratio)
        ratio = false;
    largeur = l;
}

void Resize::changeHauteur()
{
    int h = _hInput->value();
    if (_ratio->isChecked() && !ratio)
    {
        ratio = true;
        _lInput->setValue(h*_lInput->value()/hauteur);
    }
    else if (ratio)
        ratio = false;
    hauteur = h;
}
