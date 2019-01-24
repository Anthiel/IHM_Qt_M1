#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "qlabelexplorer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_actionImporter_triggered();
    void on_actionTout_supprimer_triggered();
    void on_actionRedimensionner_triggered();
    void on_actionRogner_triggered();

public slots :
    void GetLabelClick();

private:
    void enableIfPic(bool enable = true);
    void SetMainPicture(QString pic, QLabel *label);
    void SetMainPicture(const QPixmap *pixmap, QLabel *label);


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
