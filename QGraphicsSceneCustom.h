#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H
#include <QGraphicsScene>


class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT

public:
    int angle = 0;

public:
    QGraphicsSceneCustom();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    int getAngle();
    void setAngle(int a);

};

#endif // SCENECUSTOM_H
