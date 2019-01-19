#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>

#include "resize.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    enableIfPic(false);
    label_Picviewer->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void MainWindow::on_actionRedimensionner_triggered()
{
    qDebug() << __FUNCTION__ << "Old size"  << label_Picviewer->pixmap()->size().rwidth() << label_Picviewer->pixmap()->size().rheight();
    int largeur = label_Picviewer->pixmap()->size().rwidth(),
        hauteur = label_Picviewer->pixmap()->size().rheight();
    Resize w_resize;
    w_resize.setLargeur(largeur);
    w_resize.setHauteur(hauteur);
    if (w_resize.exec())
    {
        largeur = w_resize.getLargeur();
        hauteur = w_resize.getHauteur();
        label_Picviewer->setPixmap(label_Picviewer->pixmap()->scaled(largeur,hauteur));
    }

    qDebug() << __FUNCTION__ << "New size" << label_Picviewer->pixmap()->size().rwidth() << label_Picviewer->pixmap()->size().rheight();
}

void MainWindow::enableIfPic(bool enable)
{
    actionRedimensionner->setEnabled(enable);
}

void MainWindow::on_actionImporter_triggered()
{
   QString  fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)"));

   qDebug() << fileName;
   QPixmap test(fileName);
   label_Picviewer->setPixmap(test);

   enableIfPic();
}
