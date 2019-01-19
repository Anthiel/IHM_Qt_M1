#ifndef RESIZE_H
#define RESIZE_H

#include "ui_resize.h"

class Resize : public QDialog, private Ui::Resize
{
    Q_OBJECT

private:
    int largeur;
    int hauteur;
    bool ratio = false;

public:
    explicit Resize(QWidget *parent = nullptr);
    inline int  getLargeur() const {return largeur;}
    inline int  getHauteur() const {return hauteur;}
    void setLargeur(int _largeur);
    void setHauteur(int _hauteur);

private slots:
    void changeLargeur(int l);
    void changeHauteur(int h);

};

#endif // RESIZE_H
