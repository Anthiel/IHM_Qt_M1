#ifndef QGRAPHICSVIEWCUSTOM_H
#define QGRAPHICSVIEWCUSTOM_H

#include <QGraphicsView>

class QGraphicsViewCustom : public QGraphicsView
{

    Q_OBJECT

private:
    int ID;

public:
    double Xbegin = 0, Ybegin = 0;
    double Xend = 0, Yend = 0;

signals:
    void mousePressed( const QPoint& );

public:
    QGraphicsViewCustom(QWidget *parent);
    void mousePressEvent( QMouseEvent* ev );
    void mouseMoveEvent( QMouseEvent* ev );
    void mouseReleaseEvent( QMouseEvent* ev );
    void setID(int i);
    int getID();
};

#endif // QGRAPHICSVIEWCUSTOM_H
