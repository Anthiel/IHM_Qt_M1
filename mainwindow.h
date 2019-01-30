#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "qGraphicsViewCustom.h"
#include <QResizeEvent>
#include "QGraphicsSceneCustom.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    int activeScene = 0;
    int sceneInit = 0; // 0 non init / 1 init
    QGraphicsSceneCustom *sceneTab;
    QPixmap *PixmapTab;
    QGraphicsProxyWidget *proxyPixmapTab;
    QGraphicsView* view;
    int angleRotate = 0;
    int spacing = 25;
    QGraphicsViewCustom *ExplorerGraphicsView[200];
    int ImageCount=0;
    bool rognageWindowOpen = false;
    QGraphicsRectItem* itemRognage;
    QPainter *painter;




private slots:
    void on_actionImporter_triggered();
    void on_actionTout_supprimer_triggered();
    void on_actionRedimensionner_triggered();
    void on_actionRogner_triggered();

    void on_actionExporter_l_image_triggered();

    void on_actionRotation_90_triggered();

    void on_actionRoation_90_triggered();

    void on_actionRotation_triggered();

public slots :
    void GetExplorerClick();
    void RognageClick();

private:
    void enableIfPic(bool enable = true);
    //void SetMainPicture(const QPixmap *pixmap, QLabel *label);
    void SetMainPicture(QGraphicsSceneCustom *scene, QGraphicsViewCustom *PixFrame);
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent *);
    void changeEvent(QEvent *e);
    bool event(QEvent *event);
    void showTest(QGraphicsViewCustom ** t);
    void keyPressEvent(QKeyEvent *event);
    void rognageGraphique();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
