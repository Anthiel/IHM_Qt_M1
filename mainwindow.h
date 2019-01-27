#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "qlabelexplorer.h"
#include "QGraphicsViewCustom.h"
#include <QResizeEvent>

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
    QGraphicsScene *sceneTab;
    QPixmap *PixmapTab;
    QGraphicsProxyWidget *proxyPixmapTab;
    QGraphicsView* view;



private slots:
    void on_actionImporter_triggered();
    void on_actionTout_supprimer_triggered();
    void on_actionRedimensionner_triggered();
    void on_actionRogner_triggered();

    void on_actionExporter_l_image_triggered();

public slots :
    void GetLabelClick();

private:
    void enableIfPic(bool enable = true);
    //void SetMainPicture(const QPixmap *pixmap, QLabel *label);
    void SetMainPicture(QGraphicsScene *scene, QGraphicsViewCustom *PixFrame);
    void resizeEvent(QResizeEvent* event);
    void showEvent(QShowEvent *);
    void changeEvent(QEvent *e);
    bool event(QEvent *event);
    void showTest(QGraphicsViewCustom ** t);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
