
#include "historique.h"

Historique::Historique(){
    can_undo=false;
    can_redo=false;

    actual_element=0;
    first_element=0;
    last_element=0;
    tabSize=10;
    elements=new QPixmap[tabSize];
}

void Historique::on_image_added(QPixmap *image){
    elements[actual_element] = *image;
    set_actual_element();
}

Historique::~Historique(){
    if (elements){
          delete[] elements;
    }
}

void Historique::set_actual_element(){
    element=elements[actual_element];
}

void Historique::on_actionUndo_triggered(){
    qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    if(can_undo){
        actual_element--;
        if (actual_element<0){
            actual_element=tabSize-1;
        }
        if(actual_element==first_element){
            can_undo=false;
        }
        can_redo=true;
        set_actual_element();
        qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    }
}

void Historique::on_actionRedo_triggered(){
    qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    if(can_redo){
        actual_element++;
        if(actual_element>=tabSize){
            actual_element=0;
        }
        if(actual_element==last_element){
            can_redo=false;
        }
        can_undo=true;
        set_actual_element();
        qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    }
}

void Historique::on_newModification_added(QPixmap *modification){
    qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    actual_element=(actual_element+1)%tabSize;
    last_element=actual_element;
    if(actual_element==first_element){
        first_element=(first_element+1)%tabSize;
    }
    qDebug() << __FUNCTION__ << first_element << actual_element << last_element;
    can_redo=false;
    can_undo=true;
    elements[actual_element] = *modification;
    set_actual_element();
}
