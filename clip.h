#ifndef CLIP_H
#define CLIP_H

#include "ui_clip.h"

class clip : public QDialog, private Ui::Resize
{
    Q_OBJECT

private:
    int x0;
    int y0;
    int xf;
    int yf;
    int largeur;
    int hauteur;
    bool ratio = false;

public:
    explicit clip(QWidget *parent = nullptr);
    inline int  getLargeur() const {return largeur;}
    inline int  getHauteur() const {return hauteur;}
    inline int  getX0() const {return x0;}
    inline int  getY0() const {return y0;}
    void setLargeur(int _largeur);
    void setHauteur(int _hauteur);

private slots:
    void changeLargeur(int l);
    void changeHauteur(int h);
};

#endif // CLIP_H
