#ifndef HISTORIQUE_H
#define HISTORIQUE_H


class historique
{

public:
    bool can_undo;
    bool can_redo;

private:
    int actual_element;
    int first_element;
    int last_element;
    int tabSize;

public:
    historique();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_newModification_added();

private:
    void set_actual_element();
};



#endif // HISTORIQUE_H
