#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QSpacerItem>
#include <QStringList>
#include <QPixmapCache>
#include "resize.h"
#include "clip.h"

int spacing = 25;
QLabel *ImgLabel[50];
int ImageCount=0;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    enableIfPic(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionRedimensionner_triggered()
{
    qDebug() << __FUNCTION__ << "Old size"  << ui->label_Picviewer->pixmap()->size().rwidth() << ui->label_Picviewer->pixmap()->size().rheight();
    int largeur = ui->label_Picviewer->pixmap()->size().rwidth(),
        hauteur = ui->label_Picviewer->pixmap()->size().rheight();
    Resize w_resize;
    w_resize.setLargeur(largeur);
    w_resize.setHauteur(hauteur);
    if (w_resize.exec())
    {
        largeur = w_resize.getLargeur();
        hauteur = w_resize.getHauteur();
        ui->label_Picviewer->setPixmap(ui->label_Picviewer->pixmap()->scaled(largeur,hauteur));
    }

    qDebug() << __FUNCTION__ << "New size" << ui->label_Picviewer->pixmap()->size().rwidth() << ui->label_Picviewer->pixmap()->size().rheight();
}

void MainWindow::on_actionRogner_triggered()
{
    qDebug() << __FUNCTION__ << "Old size"  << ui->label_Picviewer->pixmap()->size().rwidth() << ui->label_Picviewer->pixmap()->size().rheight();
    int largeur = ui->label_Picviewer->pixmap()->size().rwidth(),
        hauteur = ui->label_Picviewer->pixmap()->size().rheight();
    Clip w_clip;
    w_clip.setLargeur(largeur);
    w_clip.setHauteur(hauteur);
    if (w_clip.exec()){
        largeur = w_clip.getLargeur();
        hauteur = w_clip.getHauteur();
        int x0=w_clip.getX0();
        int y0=w_clip.getY0();
        qDebug() << __FUNCTION__ << "hello" <<x0 << y0<<largeur<<hauteur;
        ui->label_Picviewer->setPixmap(ui->label_Picviewer->pixmap()->copy(x0,y0,largeur,hauteur));
    }

    qDebug() << __FUNCTION__ << "New size" << ui->label_Picviewer->pixmap()->size().rwidth() << ui->label_Picviewer->pixmap()->size().rheight();
}

void MainWindow::enableIfPic(bool enable)
{
    ui->actionRedimensionner->setEnabled(enable);
    ui->actionRogner->setEnabled(enable);
}


void MainWindow::on_actionImporter_triggered()
//Importation des images dans le logiciel
// label_PicViewer = label du viewer
// Layout_Explorer = label généré par le nb d'image
// LabelExpl_img = label modèle
{
   on_actionTout_supprimer_triggered(); // suppression des potentiels images présentes

   QStringList  fileNames = QFileDialog::getOpenFileNames(this,
        tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)")); // sélection des images

   ImageCount = fileNames.count(); //On veut savoir le nombre d'images présentes
   if(ImageCount <= 0) return;

   QLabel *LPics[ImageCount]; // création du tableau contenant les labels pour les images de 0+1 à i


   // chargement de l'image dans le Viewer
   QPixmap Picviewer(fileNames.at(0));
   QPixmap PicI(fileNames.at(0));
   int w = PicI.width();
   int h = PicI.height();
   ui->label_Picviewer->setFixedSize(w,h);
   ui->label_Picviewer->setPixmap(Picviewer.scaled(w,h, Qt::KeepAspectRatio)); // charge l'image
   ui->label_Picviewer->setAlignment(Qt::AlignCenter); // centre l'image dans le label

   for(int i = 0; i<ImageCount ; i++){

       if(i>0){ // si c'est la ième image, on la met dans un lael généré dans le tableau
           //ième image

           //Copie des paramètres du modèle
           LPics[i] = new QLabel(this);
           LPics[i]->setMaximumSize(ui->LabelExpl_img->maximumSize());
           LPics[i]->setMinimumSize(ui->LabelExpl_img->minimumSize());
           LPics[i]->setSizePolicy(ui->LabelExpl_img->sizePolicy());

           // chargement de l'image dans un label de l'exploreur
           int wi = LPics[i]->width();
           int hi = LPics[i]->height();
           PicI.load(fileNames.at(i));
           LPics[i]->setPixmap(PicI.scaled(wi,hi, Qt::KeepAspectRatio));
           LPics[i]->setAlignment(Qt::AlignCenter);

           ui->Layout_Explorer->addSpacing(spacing); // séparateur

           ImgLabel[i-1] = LPics[i]; // copie de l'adresse du label dans la variable globale
                                     //(indispensable pour la suppression)
           ui->Layout_Explorer->addWidget(LPics[i], Qt::AlignLeft);  // ajout du label dans le layout
       }
       else if (i==0){ //Si c'est la première image, on la met dans le laben "modèle" des autres
           ui->Layout_Explorer->setAlignment(Qt::AlignLeft);
           int wi = ui->LabelExpl_img->width();
           int hi = ui->LabelExpl_img->height();
           QPixmap PicI(fileNames.at(i));
           ui->LabelExpl_img->setPixmap(PicI.scaled(wi,hi, Qt::KeepAspectRatio));
           ui->LabelExpl_img->setAlignment(Qt::AlignCenter);
       }
   }
   enableIfPic();

}



void MainWindow::on_actionTout_supprimer_triggered()
// Suppression de toutes les images (viewer et explorateur)
{
    if(ImageCount < 1){
        return;
    }
    int tailleImgLabel = sizeof(ImgLabel)/sizeof(ImgLabel[0]);
    ui->LabelExpl_img->setPixmap(QPixmap());
    ui->label_Picviewer->setPixmap(QPixmap());

    for(int i=0; i<ImageCount-1;i++)
        ImgLabel[i]->setPixmap(QPixmap());

    while(ui->Layout_Explorer->count()>1)
        ui->Layout_Explorer->removeWidget(ui->Layout_Explorer->itemAt(1)->widget());

    for(int i = 0; i<tailleImgLabel;i++)
        ImgLabel[i] = 0;

    ImageCount = 0;
    enableIfPic(false);
}
