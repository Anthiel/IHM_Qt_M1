#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QGraphicsView>

class QGraphicsViewCustom : public QGraphicsView
{

    Q_OBJECT

private:
    int ID;

signals:
    void mousePressed( const QPoint& );

public:
    QGraphicsViewCustom(QWidget *parent);
    void mousePressEvent( QMouseEvent* ev );
    void setID(int i);
    int getID();
};

#endif // QGRAPHICSVIEWCUSTOM_H
