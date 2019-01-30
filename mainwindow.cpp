#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QSpacerItem>
#include <QStringList>
#include <QPixmapCache>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include "qGraphicsViewCustom.h"
#include <QResizeEvent>
#include <QCloseEvent>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resize.h"
#include "clip.h"
#include "rotate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PixFrame->setStyleSheet("background: transparent; border: 0px");
    ui->GraphicModeleExplorer->setStyleSheet("background: transparent; border: 0px");
    enableIfPic(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (ImageCount > 0)
    {
        switch (QMessageBox::question(this,
                                      "Enregistrer les modifications ?",
                                      "Vos modifications seront perdues si vous ne les enregistrez pas.",
                                      QMessageBox::No | QMessageBox::Cancel | QMessageBox::Save))
        {
            case QMessageBox::No:
                event->accept();
                break;
            case QMessageBox::Save:
                on_actionExporter_l_image_triggered();
                break;
            default:
                event->ignore();
        }
    }
}

void MainWindow::on_actionRedimensionner_triggered()
{
    int IDpix = ui->PixFrame->getID();
    qDebug() << __FUNCTION__ << "Old size" << PixmapTab[IDpix].size().rwidth() <<  PixmapTab[IDpix].size().rheight();
    int largeur = PixmapTab[IDpix].size().rwidth(),
        hauteur = PixmapTab[IDpix].size().rheight();
    Resize w_resize;
    w_resize.setLargeur(largeur);
    w_resize.setHauteur(hauteur);
    if (w_resize.exec())
    {
        largeur = w_resize.getLargeur();
        hauteur = w_resize.getHauteur();
        sceneTab[IDpix].clear();
        sceneTab[IDpix].addPixmap(PixmapTab[IDpix].scaled(largeur,hauteur));
        PixmapTab[IDpix] = PixmapTab[IDpix].scaled(largeur,hauteur);
    }

    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    qDebug() << __FUNCTION__ << "New size" << PixmapTab[IDpix].size().rwidth() << PixmapTab[IDpix].size().rheight();
}

void MainWindow::resizeEvent(QResizeEvent* event) // quand la taille de la fenetre change
{
    if(sceneInit){
        QMainWindow::resizeEvent(event);
        ui->PixFrame->fitInView(sceneTab[activeScene].sceneRect(),Qt::KeepAspectRatio);
    }
}

void MainWindow::showEvent(QShowEvent *) {}

void MainWindow::on_actionNoir_et_Blanc_triggered()
{
    int id_pix = ui->PixFrame->getID();
    int largeur = PixmapTab[id_pix].size().rwidth(),
        hauteur = PixmapTab[id_pix].size().rheight();
    QImage im = PixmapTab[id_pix].toImage();
    for (int x = 0 ; x < largeur ; x++)
        for (int y = 0 ; y < hauteur ; y++)
        {
            int color = qGray(im.pixel(x,y));
            im.setPixel(x,y, qRgb(color,color,color));
        }

    sceneTab[id_pix].clear();
    sceneTab[id_pix].addPixmap(QPixmap::fromImage(im));
    PixmapTab[id_pix] = QPixmap::fromImage(im);

}

void MainWindow::on_actionRogner_triggered()
{
    int IDpix = ui->PixFrame->getID();
    qDebug() << __FUNCTION__ << "Old size"  << PixmapTab[IDpix].size().rwidth() <<  PixmapTab[IDpix].size().rheight();

    int largeur = PixmapTab[IDpix].size().rwidth(),
        hauteur = PixmapTab[IDpix].size().rheight();
    Clip w_clip;
    w_clip.setLargeur(largeur);
    w_clip.setHauteur(hauteur);
    if (w_clip.exec()){
        largeur = w_clip.getLargeur();
        hauteur = w_clip.getHauteur();
        int x0=w_clip.getX0();
        int y0=w_clip.getY0();
        qDebug() << __FUNCTION__ << "hello" <<x0 << y0<<largeur<<hauteur;
        sceneTab[IDpix].clear();
        sceneTab[IDpix].addPixmap(PixmapTab[IDpix].copy(x0,y0,largeur,hauteur));
        PixmapTab[IDpix] = PixmapTab[IDpix].copy(x0,y0,largeur,hauteur);
    }
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    qDebug() << __FUNCTION__ << "New size" << PixmapTab[IDpix].size().rwidth() << PixmapTab[IDpix].size().rheight();
}

void MainWindow::enableIfPic(bool enable)
{
    ui->actionRedimensionner->setEnabled(enable);
    ui->actionRogner->setEnabled(enable);
}

void MainWindow::SetMainPicture(QGraphicsScene *scene, QGraphicsViewCustom *PixFrame)
{
    PixFrame->setScene(scene);
    PixFrame->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    PixFrame->setID(activeScene);
}


void MainWindow::GetLabelClick(){

    ExplorerGraphicsView[activeScene]->setStyleSheet("background: transparent; border: 0px");
    QGraphicsViewCustom *src = qobject_cast<QGraphicsViewCustom *>(sender());
    activeScene = src->getID();
    ExplorerGraphicsView[activeScene]->setStyleSheet("background: transparent; border: 1px solid blue");

    //refresh de la taille des images dans l'explorer
    for(int i=0; i< ImageCount;i++){
        ExplorerGraphicsView[i]->fitInView(sceneTab[i].sceneRect(), Qt::KeepAspectRatio);
    }

    SetMainPicture(&sceneTab[activeScene],  ui->PixFrame);

}

void MainWindow::showTest(QGraphicsViewCustom ** t){

}

bool MainWindow::event(QEvent *event)
{
    if(event->type() == QEvent::Paint)
        if(sceneInit == 1)
            for(int i = 0; i<ImageCount ; i++)
                 ExplorerGraphicsView[i]->fitInView(sceneTab[i].sceneRect(),Qt::KeepAspectRatio);
    return QWidget::event(event);
}

void MainWindow::changeEvent(QEvent *e){
    if(sceneInit){
       /* for(int i = 0; i<ImageCount ; i++){
            ExplorerGraphicsView[i]->fitInView(sceneTab[i].sceneRect(),Qt::KeepAspectRatio);
        }*/
    }
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


    //initialisation des scènes

    sceneTab = new QGraphicsScene[uint(ImageCount)];
    PixmapTab = new QPixmap[uint(ImageCount)];
    activeScene = 0;

    QImage *imageObject = new QImage();
    QPixmap image;

    for(int i=0; i<ImageCount; i++){
        imageObject->load(fileNames.at(i));
        image = QPixmap::fromImage(*imageObject);
        sceneTab[i].addPixmap(image);
        sceneTab[i].setSceneRect(image.rect());
        PixmapTab[i] = image;
     }

    QGraphicsViewCustom **ExplorerPics  = new QGraphicsViewCustom*[uint(ImageCount)]; // création du tableau contenant les labels pour les images de 0+1 à i
    // chargement de l'image dans le Viewer

    SetMainPicture(&sceneTab[0], ui->PixFrame);

    QPixmap PicI;
    ExplorerPics[0] = ui-> GraphicModeleExplorer;
    ui->Layout_Explorer->setAlignment(Qt::AlignLeft);

    for(int i = 0; i<ImageCount ; i++){
        if(i>0){ // si c'est la ième image, Copie des paramètres du modèle
             ExplorerPics[i] = new QGraphicsViewCustom(ui->GraphicModeleExplorer);
             ExplorerPics[i]->setStyleSheet("background: transparent; border: 0px");
             ExplorerPics[i]->setMaximumSize(ui->GraphicModeleExplorer->maximumSize());
             ExplorerPics[i]->setMinimumSize(ui->GraphicModeleExplorer->minimumSize());
             ExplorerPics[i]->setSizePolicy(ui->GraphicModeleExplorer->sizePolicy());
        }
        if(i == 0)
             ExplorerPics[i]->setStyleSheet("background: transparent; border: 1px solid blue");

        connect(ExplorerPics[i], SIGNAL(mousePressed(const QPoint&)),this, SLOT(GetLabelClick()));

        if(i>0)ui->Layout_Explorer->addSpacing(spacing); // séparateur
        ExplorerGraphicsView[i] = ExplorerPics[i]; // copie de l'adresse du label dans la variable globale
                                      //(indispensable pour la suppression)
        if(i>0) ui->Layout_Explorer->addWidget(ExplorerPics[i], Qt::AlignLeft);  // ajout du label dans le layout
        ExplorerPics[i]->setScene(&sceneTab[i]);

        // chargement de l'image dans un label de l'exploreur
        ExplorerPics[i]->fitInView(sceneTab[i].sceneRect(),Qt::KeepAspectRatio);
        ExplorerPics[i]->setID(i);
        ExplorerPics[i]->setAlignment(Qt::AlignCenter);
    }
    /*
    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,400,400);
    QPen pen(Qt::white, 10, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
    item1->setBrush(Qt::NoBrush);
    item1->setPen(pen);
    sceneTab[0].addItem(item1);

*/
    enableIfPic();
    delete [] ExplorerPics;
    ExplorerPics = nullptr;
    sceneInit = 1;
}


void MainWindow::on_actionTout_supprimer_triggered()
// Suppression de toutes les images (viewer et explorateur)
{
    qDebug() << ImageCount;
    if(ImageCount < 1)
        return;    

    for(int i=0; i<ImageCount;i++){
        sceneTab[i].clear();
        PixmapTab[i] = QPixmap();
    }
    ExplorerGraphicsView[activeScene]->setStyleSheet("background: transparent; border: 0px");
    while(ui->Layout_Explorer->count()>1){
        ui->Layout_Explorer->removeWidget(ui->Layout_Explorer->itemAt(1)->widget());
    }
    for(int i = 0; i<ImageCount;i++)
        ExplorerGraphicsView[i] = nullptr;

    ImageCount = 0;
    sceneInit = 0;
    enableIfPic(false);
    sceneTab = nullptr;
    PixmapTab = nullptr;
}

void MainWindow::on_actionExporter_l_image_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/",
                               tr("Images (*.png *.bmp *.jpg)", "Images(*.jpg)"));
     //On veut savoir le nombre d'images présentes
    if(fileName.count() <= 0) return;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    PixmapTab[activeScene].save(&file);
}

void MainWindow::on_actionRotation_90_triggered()
// rotation à 90° du pixmap
{
    int IDpix = ui->PixFrame->getID();
    QTransform transform;
    transform.rotate(90+angleRotate);
    PixmapTab[IDpix] = PixmapTab[IDpix].transformed(transform);
    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    angleRotate = 90 + angleRotate;
}

void MainWindow::on_actionRoation_90_triggered()
// rotation à -90° du pixmap
{
    int IDpix = ui->PixFrame->getID();
    QTransform transform;
    transform.rotate(-90+angleRotate);
    PixmapTab[IDpix] = PixmapTab[IDpix].transformed(transform);
    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    angleRotate = -90 + angleRotate;
}

void MainWindow::on_actionRotation_triggered()
{
    Rotate rotateWindow;
    qDebug() << "debut " << angleRotate;
    rotateWindow.setInfo(&PixmapTab[activeScene], &sceneTab[activeScene], ui->PixFrame, angleRotate);

    if (rotateWindow.exec())
    {}
    angleRotate = rotateWindow.getAngle();
    qDebug() << "fin " << angleRotate;

    ;
}
