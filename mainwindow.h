#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

private:
    void enableIfPic(bool enable = true);

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_actionImporter_triggered();
    void on_actionRedimensionner_triggered();
};

#endif // MAINWINDOW_H
