
#include <QDebug>
#include "resize.h"

Resize::Resize(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(_lInput, SIGNAL(valueChanged(int)), this, SLOT(changeLargeur()));
    connect(_hInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur()));
    connect(_ratio, SIGNAL(stateChanged(int)), this, SLOT(calculRatio()));
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
    if (_ratio->isChecked() && ratio)
    {
        ratio=false;
        _hInput->setValue((l*ratio_h)/ratio_l);
    }
    else if(!ratio)
    {
        ratio=true;
    }
    largeur = l;
    qDebug() << __FUNCTION__ << l;
}

void Resize::changeHauteur()
{
    int h = _hInput->value();
    if (_ratio->isChecked() && ratio)
    {
        ratio=false;
        _lInput->setValue((h*ratio_l)/ratio_h);
    }
    else if(!ratio)
    {
        ratio=true;
    }
    hauteur = h;
    qDebug() << __FUNCTION__ << h;
}

void Resize::calculRatio()
{
    if (_ratio->isChecked())
    {
        ratio_h=hauteur;
        ratio_l=largeur;
        ratio=true;
    }
}
