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
    bool openWindow = false;

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
    void changeLargeur();
    void changeHauteur();
    void changeX0();
    void changeY0();
    void changeXf();
    void changeYf();
    void on_modeGraphique_clicked();
};

#endif // CLIP_H
