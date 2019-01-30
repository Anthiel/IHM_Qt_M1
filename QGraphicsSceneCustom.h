#ifndef QGRAPHICSSCENECUSTOM_H
#define QGRAPHICSSCENECUSTOM_H
#include <QGraphicsScene>


class QGraphicsSceneCustom : public QGraphicsScene
{
    Q_OBJECT

public:
    QGraphicsSceneCustom();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);

};

#endif // SCENECUSTOM_H
