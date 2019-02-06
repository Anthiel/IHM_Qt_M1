#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <QPixmap>
#include <QDebug>

class Historique
{

public:
    bool can_undo;
    bool can_redo;
    QPixmap element;

private:
    int actual_element;
    int first_element;
    int last_element;
    int tabSize;
    QPixmap *elements;

public:
    Historique();
    ~Historique();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_newModification_added(QPixmap *modification);
    void on_image_added(QPixmap *image);


private:
    void set_actual_element();
};



#endif // HISTORIQUE_H
