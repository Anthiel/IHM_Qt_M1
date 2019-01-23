#ifndef CLIP_H
#define CLIP_H
#include <QDebug>
#include "ui_clip.h"

class Clip : public QDialog, private Ui::Clip
{
    Q_OBJECT

private:
    int x0;
    int y0;
    int xf;
    int yf;
    int largeur;
    int hauteur;
    int maxlargeur;
    int maxhauteur;

public:
    explicit Clip(QWidget *parent = nullptr);
    inline int  getLargeur() const {return largeur;}
    inline int  getHauteur() const {return hauteur;}
    inline int  getX0() const {return x0;}
    inline int  getY0() const {return y0;}
    inline int  getXf() const {return xf;}
    inline int  getYf() const {return yf;}
    void setLargeur(int _largeur);
    void setHauteur(int _hauteur);

private slots:
    void changeLargeur(int l);
    void changeHauteur(int h);
    void changeX0(int x0);
    void changeY0(int y0);
    void changeXf(int xf);
    void changeYf(int yf);
};

#endif // CLIP_H
