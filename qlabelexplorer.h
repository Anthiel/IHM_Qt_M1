#ifndef QLABELEXPLORER_H
#define QLABELEXPLORER_H

#include <QLabel>

class QLabelExplorer : public QLabel
{

    Q_OBJECT

private:
    QString URLimage;

signals:
    void mousePressed( const QPoint& );

public:
    QLabelExplorer(QWidget *parent);
    void mousePressEvent( QMouseEvent* ev );
    void setUrlImage(QString img);
    QString getUrlImage();
};

#endif // QLABELEXPLORER_H
