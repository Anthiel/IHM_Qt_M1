#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_Picviewer->setScaledContents( true );
    ui->label_Picviewer->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionImporter_triggered()
{
   QString  fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)"));

   qDebug() << fileName;
   QPixmap test(fileName);
   ui->label_Picviewer->setPixmap(test);
}
