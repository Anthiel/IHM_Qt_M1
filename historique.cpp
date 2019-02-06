#include <QPixmap>
#include <QDebug>
#include "historique.h"

historique::historique(){
    can_undo=false;
    can_redo=false;

    actual_element=0;
    first_element=0;
    last_element=0;
    tabSize;
}


void historique::on_actionUndo_triggered(){
    if(can_undo){
        actual_element=(actual_element-1)%tabSize;
        if(actual_element==first_element){
            can_undo=false;
        }
        can_redo=true;
        //set_actual_element();
    }
}

void historique::on_actionRedo_triggered(){
    if(can_redo){
        actual_element=(actual_element+1)%tabSize;
        if(actual_element==last_element){
            can_redo=false;
        }
        can_undo=true;
        //set_actual_element();
    }
}

void historique::on_newModification_added(){
    actual_element=(actual_element+1)%tabSize;
    last_element=actual_element;
    if(actual_element==first_element){
        first_element=(first_element+1)%tabSize;
    }
    can_redo=false;
    can_undo=true;
    //set_actual_element();
}
/*
void set_actual_element(){

}
*/
