#include <QDebug>
#include "clip.h"

Clip::Clip(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(_lInput, SIGNAL(valueChanged(int)), this, SLOT(changeLargeur(int)));
    connect(_hInput, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));
    connect(_x0Input, SIGNAL(valueChanged(int)), this, SLOT(changeX0(int)));
    connect(_y0Input, SIGNAL(valueChanged(int)), this, SLOT(changeY0(int)));
    connect(_xfInput, SIGNAL(valueChanged(int)), this, SLOT(changeXf(int)));
    connect(_yfInput, SIGNAL(valueChanged(int)), this, SLOT(changeYf(int)));
}

void Clip::setLargeur(int _largeur)
{
    x0=0;
    _x0Input->setValue(x0);
    largeur=_largeur;
    maxlargeur=_largeur;
    _lInput->setValue(largeur);
    xf=_largeur;
    _xfInput->setValue(xf);
    qDebug() << __FUNCTION__ <<_largeur ;
}
void Clip::setHauteur(int _hauteur)
{
    y0=0;
    _y0Input->setValue(y0);
    hauteur=_hauteur;
    maxhauteur=_hauteur;
    _hInput->setValue(hauteur);
    yf=_hauteur;
    _yfInput->setValue(yf);
    qDebug() << __FUNCTION__ << _hauteur ;
}

void Clip::changeLargeur(int l){
    if (l>maxlargeur-x0){
        l=maxlargeur-x0;
        _lInput->setValue(l);
    }
    if(l<1){
        l=1;
        _lInput->setValue(l);
    }
    largeur=l;
    xf=x0+largeur;
    _xfInput->setValue(xf);
    qDebug() << __FUNCTION__ << l;
}

void Clip::changeHauteur(int h){
    if (h>maxhauteur-y0){
        h=maxhauteur-y0;
        _hInput->setValue(h);
    }
    if (h<1){
        h=1;
        _hInput->setValue(h);
    }
    hauteur=h;
    yf=y0+hauteur;
    _yfInput->setValue(yf);
    qDebug() << __FUNCTION__ << h;
}

void Clip::changeX0(int x){
    if(x>maxlargeur-1){
        x=maxlargeur-1;
        _x0Input->setValue(x);
    }
    if(x>xf){
        x=xf-1;
        _x0Input->setValue(x);
    }
    if(x<0){
        x=0;
        _x0Input->setValue(x);
    }
    x0=x;
    largeur=xf-x0;
    _lInput->setValue(largeur);
    qDebug() << __FUNCTION__ << x;
}

void Clip::changeY0(int y){
    if(y>maxhauteur-1){
        y=maxhauteur-1;
        _y0Input->setValue(y);
    }
    if(y>yf){
        y=yf-1;
        _y0Input->setValue(y);
    }
    if(y<0){
        y=0;
        _y0Input->setValue(y);
    }
    y0=y;
    hauteur=yf-y0;
    _hInput->setValue(hauteur);
    qDebug() << __FUNCTION__ << y;
}

void Clip::changeXf(int x){
    if(x>maxlargeur){
        x=maxlargeur;
        _xfInput->setValue(x);
    }
    if(x<1){
        x=1;
        _xfInput->setValue(x);
    }
    if(x<x0){
        x=x0+1;
        _xfInput->setValue(x);
    }
    xf=x;
    largeur=xf-x0;
    _lInput->setValue(largeur);
    qDebug() << __FUNCTION__ << x;
}

void Clip::changeYf(int y){
    if(y>maxhauteur){
        y=maxhauteur;
        _yfInput->setValue(y);
    }
    if(y<1){
        y=1;
        _yfInput->setValue(y);
    }
    if(y<y0){
        y=y0+1;
        _yfInput->setValue(y);
    }
    yf=y;
    hauteur=yf-y0;
    _hInput->setValue(hauteur);
    qDebug() << __FUNCTION__ << y;
}
