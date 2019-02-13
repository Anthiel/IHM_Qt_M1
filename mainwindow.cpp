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
#include <math.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resize.h"
#include "clip.h"
#include <QGraphicsPixmapItem>
#include <QPainter>
#include "qGraphicsViewCustom.h"
#include <QResizeEvent>
#include "rotate.h"
#include "QGraphicsSceneCustom.h"
#include "colorfilter.h"
#include "historique.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PixFrame->setStyleSheet("background: transparent; border: 0px");
    ui->carteMentale->setStyleSheet("background: transparent; border: 0px");
    connect(ui->PixFrame, SIGNAL(mousePressed(const QPoint&)),this, SLOT(ClickOnFrame()));    
    connect(ui->button_crop, SIGNAL(clicked()),this,SLOT(on_actionRogner_triggered()));
    connect(ui->button_b_a_w, SIGNAL(clicked()), this, SLOT(on_actionNoir_et_Blanc_triggered()));
    connect(ui->button_delete_all, SIGNAL(clicked()), this, SLOT(on_actionTout_supprimer_triggered()));
    connect(ui->button_import, SIGNAL(clicked()), this, SLOT(on_actionImporter_triggered()));
    connect(ui->button_resize, SIGNAL(clicked()), this, SLOT(on_actionRedimensionner_triggered()));
    connect(ui->button_rotate, SIGNAL(clicked()), this, SLOT(on_actionRotation_triggered()));
    connect(ui->button_rotate_h, SIGNAL(clicked()), this, SLOT(on_actionRotation_90_triggered()));
    connect(ui->button_rotate_ah, SIGNAL(clicked()), this, SLOT(on_actionRoation_90_triggered()));
    connect(ui->button_SelecRect, SIGNAL(clicked()), this, SLOT(on_Button_SelecRect_clicked()));
    connect(ui->button_SelecEllipse, SIGNAL(clicked()), this, SLOT(on_Button_SelecEllipse_clicked()));
    connect(ui->button_color_filter, SIGNAL(clicked()), this, SLOT(on_actionCouleurs_triggered()));
    connect(ui->button_SelecTriangle, SIGNAL(clicked()), this, SLOT(on_Button_SelecTriangle_clicked()));
    connect(ui->button_QuitSelectMode, SIGNAL(clicked()), this, SLOT(on_Button_QuitSelectMode_clicked()));
    ui->GraphicModeleExplorer->setStyleSheet("background: transparent; border: 0px");
    enableIfPic(false);

}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (sceneInit)
    {
        QPoint num_pixels = event->angleDelta();
        zoom(num_pixels.y());
    }
}


void MainWindow::colorFilter(QColor to_select, int thr, QColor colorize)
{
    bool* tab = selectByColor(to_select, thr*3);
    int id_pix = ui->PixFrame->getID();
    int largeur = PixmapTab[id_pix].size().rwidth(),
        hauteur = PixmapTab[id_pix].size().rheight();
    QImage im = PixmapTab[id_pix].toImage();
    QImage al = im.alphaChannel(); // Alpha à part

    int hue = colorize.hue();

    for (int x = 0 ; x < largeur ; x++)
        for (int y = 0 ; y < hauteur ; y++)
        {
            int a = qAlpha(im.pixel(x,y));
            if (a > 0 && tab[x*hauteur+y]) // Ne modifie que si non transparent
            {
                QColor color = im.pixel(x,y);
                color.setHsv(hue,color.saturation(), color.value());
                im.setPixelColor(x,y,color);
                al.setPixel(x,y,a);
            }
        }

    im.setAlphaChannel(al);
    sceneTab[id_pix].clear();
    sceneTab[id_pix].addPixmap(QPixmap::fromImage(im));
    PixmapTab[id_pix] = QPixmap::fromImage(im);
    delete tab;
}


void MainWindow::resizeEvent(QResizeEvent* event) // quand la taille de la fenetre change
{
    if(sceneInit){
        QMainWindow::resizeEvent(event);
        ui->PixFrame->fitInView(sceneTab[activeScene].sceneRect(),Qt::KeepAspectRatio);
        ui->carteMentale->fitInView(sceneTab[activeScene].sceneRect(),Qt::KeepAspectRatio);
    }
}

void MainWindow::showEvent(QShowEvent *) {}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()) {
            case (Qt::Key_Control):
                selectionTouch = false;
                break;
            case (Qt::Key_Shift):
                selectionShiftTouch = false;
                break;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
            case (Qt::Key_Control):
                selectionTouch = true;
                break;
            case (Qt::Key_Shift):
                selectionShiftTouch = true;
                break;
            case (Qt::Key_Enter) :
                if(rognageWindowOpen){
                    rognageGraphique();
                    rognageWindowOpen = false;
                }
                break;
            case (Qt::Key_Return) :
                if(rognageWindowOpen){
                    rognageGraphique();
                    rognageWindowOpen = false;
                }
                break;
    }

}



void MainWindow::enableIfPic(bool enable)
{
    ui->actionRedimensionner->setEnabled(enable);
    ui->actionRogner->setEnabled(enable);
    ui->actionTout_supprimer->setEnabled(enable);
    ui->actionNoir_et_Blanc->setEnabled(enable);
    ui->actionExporter_l_image->setEnabled(enable);
    ui->actionRotation->setEnabled(enable);
    ui->actionRotation_90->setEnabled(enable);
    ui->actionRoation_90->setEnabled(enable);
    ui->actionCouleurs->setEnabled(enable);
    ui->actionZoomUp->setEnabled(enable);
    ui->actionZoomDown->setEnabled(enable);
    ui->actionZoomDefault->setEnabled(enable);

    ui->actionAnnuler->setEnabled(enable);
    ui->actionRetablir->setEnabled(enable);
}

void MainWindow::SetMainPicture(QGraphicsSceneCustom *scene, QGraphicsViewCustom *PixFrame)
{
    PixFrame->setScene(scene);
    PixFrame->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    PixFrame->setID(activeScene);
}

void MainWindow::GetExplorerClick(){
    QGraphicsViewCustom *src = qobject_cast<QGraphicsViewCustom *>(sender());
    //if(activeScene == src->getID()) return;
    int ID = src->getID();
    int end = SelectionMultiple.back();
    int begin = SelectionMultiple.front();

    if(selectionTouch) // touche CTRL
        SelectionMultiple.push_back(ID);

    else if(selectionShiftTouch){ // touche SHIFT
        if(end < ID)
            for(int i = end +1; i <= ID;i++)
                 SelectionMultiple.push_back(i);
        else
            for(int i = ID; i <= begin;i++)
                 SelectionMultiple.push_back(i);
    }
    else{
        SelectionMultiple.clear();
        SelectionMultiple.push_back(ID);
    }

    if(SelectionMultiple.size() == 1)
        activeScene = ID;

    std::sort(SelectionMultiple.begin(), SelectionMultiple.end());
    SelectionMultiple.erase(std::unique(SelectionMultiple.begin(), SelectionMultiple.end()), SelectionMultiple.end());

    for(int i = 0; i<ImageCount ;i++)
        ExplorerGraphicsView[i]->setStyleSheet("background: transparent; border: 0px");
    for(int i = 0; i< SelectionMultiple.size(); i++)
        ExplorerGraphicsView[SelectionMultiple.at(i)]->setStyleSheet("background: transparent; border: 2px solid blue");

    //refresh de la taille des images dans l'explorer
    for(int i=0; i< ImageCount;i++)
        ExplorerGraphicsView[i]->fitInView(sceneTab[i].sceneRect(), Qt::KeepAspectRatio);

    SetMainPicture(&sceneTab[activeScene],  ui->PixFrame);
    SetMainPicture(&sceneTab[activeScene],  ui->carteMentale);
}

void MainWindow::drawTriangleSelection(double xb, double yb, double xe, double ye){
    QPixmap tmp = PixmapTab[activeScene];

    painter->setRenderHint(QPainter::Antialiasing);

    //ellipse
    QPen pen(Qt::white, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    int x1 = xb, x2 = xe;
    int y1 = yb, y2 = ye;
    painter->drawLine(x1+(x2-x1)/2,y1,x1,y2);
    painter->drawLine(x1,y2,x2,y2);
    painter->drawLine(x2,y2,x1+(x2-x1)/2,y1);

    // poignets
    int xB = ui->PixFrame->Xbegin; int yB = ui->PixFrame->Ybegin;
    int xE = ui->PixFrame->Xend; int yE = ui->PixFrame->Yend;
    QPen penPoignet(Qt::red, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(penPoignet);
    int largeur = PixmapTab[activeScene].width()/50;
    painter->drawEllipse(xE-largeur/2,yE-largeur/2,largeur,largeur );
    painter->drawEllipse(xB-largeur/2,yB-largeur/2,largeur,largeur );

}

void MainWindow::drawEllipseSelection(double xb, double yb, double xe, double ye){
    QPixmap tmp = PixmapTab[activeScene];

    painter->setRenderHint(QPainter::Antialiasing);

    //ellipse
    QPen pen(Qt::white, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawEllipse(xb,yb,xe-xb,ye-yb);

    // poignets
    int xB = ui->PixFrame->Xbegin; int yB = ui->PixFrame->Ybegin;
    int xE = ui->PixFrame->Xend; int yE = ui->PixFrame->Yend;
    QPen penPoignet(Qt::red, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(penPoignet);
    int largeur = PixmapTab[activeScene].width()/50;
    painter->drawEllipse(xE-largeur/2,yE-largeur/2,largeur,largeur );
    painter->drawEllipse(xB-largeur/2,yB-largeur/2,largeur,largeur );

}

void MainWindow::drawRectSelection(double xb, double yb, double xe, double ye){

    QPixmap tmp = PixmapTab[activeScene];

    painter->setRenderHint(QPainter::Antialiasing);

    //rectangle
    QPen pen(Qt::white, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);
    painter->drawRect(xb,yb,xe-xb,ye-yb);

    // Règle des tiers
    QPen penTier(Qt::white, PixmapTab[activeScene].width()/100/2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(penTier);
    double x1 = xb + (xe-xb)/3;
    double x2 = xb + 2*((xe-xb)/3);
    double y1 = yb + (ye-yb)/3;
    double y2 = yb + 2*((ye-yb)/3);
    painter->drawLine(x1,yb, x1 , ye);
    painter->drawLine(x2,yb, x2 , ye);
    painter->drawLine(xb,y1, xe , y1);
    painter->drawLine(xb,y2, xe , y2);

    // poignets
    int xB = ui->PixFrame->Xbegin; int yB = ui->PixFrame->Ybegin;
    int xE = ui->PixFrame->Xend; int yE = ui->PixFrame->Yend;
    QPen penPoignet(Qt::red, PixmapTab[activeScene].width()/100, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(penPoignet);
    int largeur = PixmapTab[activeScene].width()/50;
    painter->drawEllipse(xE-largeur/2,yE-largeur/2,largeur,largeur );
    painter->drawEllipse(xB-largeur/2,yB-largeur/2,largeur,largeur );

}

void MainWindow::updateSelectionPoint(int xb, int yb, int xe, int ye){
    ui->PixFrame->Xbegin = xb,ui->PixFrame->Ybegin = yb, ui->PixFrame->Xend = xe, ui->PixFrame->Yend = ye;
}

void MainWindow::PoignetUpdate(){

    int x = ui->PixFrame->x1;    int y = ui->PixFrame->y1;
    int xB = ui->PixFrame->Xbegin; int yB = ui->PixFrame->Ybegin;
    int xE = ui->PixFrame->Xend; int yE = ui->PixFrame->Yend;

    double distanceBegin = sqrt(pow(xB-x, 2)+pow(yB-y, 2));
    double distanceEnd = sqrt(pow(xE-x, 2)+pow(yE-y, 2));

    if(distanceEnd<distanceBegin)
        updateSelectionPoint(xB, yB, x, y);
    else
        updateSelectionPoint(x, y, xE, yE);

}


void MainWindow::ClickOnFrame(){
    if(initImport == false) return;
    QPixmap tmp = PixmapTab[activeScene];
    painter = new QPainter(&PixmapTab[activeScene]);

    if(rognageWindowOpen){
        if(!ui->PixFrame->SelectCreer)
            drawRectSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
        else if(ui->PixFrame->SelectCreer){
            drawRectSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
            PoignetUpdate();
        }
    }

    if(Selection == true){
        qDebug() << "selection activée";
        if(SelecMode == 0){ // Triangle
            qDebug() << "selection Triangle";
            if(!ui->PixFrame->SelectCreer)
                drawTriangleSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
            else if(ui->PixFrame->SelectCreer){
                drawTriangleSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
                PoignetUpdate();
            }
        }
        else if(SelecMode == 1){ // Ellipse
            qDebug() << "selection Ellipse";
            if(!ui->PixFrame->SelectCreer)
                drawEllipseSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
            else if(ui->PixFrame->SelectCreer){
                drawEllipseSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
                PoignetUpdate();
            }
        }
        else if(SelecMode == 2){ // Rectangle
            qDebug() << "selection Rectangle";
            if(!ui->PixFrame->SelectCreer)
                drawRectSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
            else if(ui->PixFrame->SelectCreer){
                drawRectSelection(ui->PixFrame->Xbegin,ui->PixFrame->Ybegin, ui->PixFrame->Xend, ui->PixFrame->Yend);
                PoignetUpdate();
            }
        }

    }


    sceneTab[activeScene].clear();
    sceneTab[activeScene].addPixmap(PixmapTab[activeScene]);

    delete painter;
    PixmapTab[activeScene] = tmp;

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

bool* MainWindow::selectByColor(QColor color, uint thr)
{
    int id_pix = ui->PixFrame->getID();
    int largeur = PixmapTab[id_pix].size().rwidth(),
        hauteur = PixmapTab[id_pix].size().rheight();

    QImage im = PixmapTab[id_pix].toImage();
    bool* selected = new bool[largeur*hauteur];

    for (int x = 0 ; x < largeur ; x++)
        for (int y = 0 ; y < hauteur ; y++)
        {
            QColor o_color = im.pixel(x,y);
            int a = qAlpha(im.pixel(x,y));
            /* Calcul de la différence de couleur à partir de la couleur passée */
            uint diff = abs(o_color.red() - color.red()) +
                        abs(o_color.green() - color.green()) +
                        abs(o_color.blue() - color.blue());
            /* + abs(a - color.alpha()*/
            selected[x*hauteur+y] = (diff < thr);
        }

    return selected;
}

void MainWindow::zoom(double z_ratio)
{

    if ((z_ratio > 0 && zoom_value < 500.0) || (z_ratio < 0 && zoom_value > 50.0))
    {
        zoom_value += z_ratio/60;
        int id_pix = ui->PixFrame->getID();
        QPixmap pix = historiqueTab[ui->PixFrame->getID()].element;
        PixmapTab[id_pix] = pix.scaled(pix.width()*zoom_value/100,pix.height()*zoom_value/100);
        sceneTab[id_pix].clear();
        sceneTab[id_pix].addPixmap(PixmapTab[id_pix]);
        sceneTab[id_pix].setSceneRect(PixmapTab[id_pix].rect());
    }
}

void MainWindow::on_actionZoomUp_triggered()
{
    zoom(600.0);
}
void MainWindow::on_actionZoomDown_triggered()
{
    zoom(-600);
}
void MainWindow::on_actionZoomDefault_triggered()
{
    zoom_value = 100;
    int id_pix = ui->PixFrame->getID();
    QPixmap pix = historiqueTab[ui->PixFrame->getID()].element;
    PixmapTab[id_pix] = pix.scaled(pix.width(),pix.height());
    sceneTab[id_pix].clear();
    sceneTab[id_pix].addPixmap(PixmapTab[id_pix]);
    sceneTab[id_pix].setSceneRect(PixmapTab[id_pix].rect());
}

void MainWindow::on_actionImporter_triggered()
//Importation des images dans le logiciel
// label_PicViewer = label du viewer
// Layout_Explorer = label généré par le nb d'image
// LabelExpl_img = label modèle
{
    on_actionTout_supprimer_triggered(); // suppression des potentiels images présentes
    ui->Layout_Explorer->setAlignment(Qt::AlignLeft);
    ui->GraphicModeleExplorer->setAlignment(Qt::AlignLeft);
    QStringList  fileNames = QFileDialog::getOpenFileNames(this,
         tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)")); // sélection des images


    ImageCount = fileNames.count(); //On veut savoir le nombre d'images présentes
    if(ImageCount <= 0) return;


    //initialisation des scènes

    sceneTab = new QGraphicsSceneCustom[uint(ImageCount)];
    PixmapTab = new QPixmap[uint(ImageCount)];
    historiqueTab = new Historique[uint(ImageCount)];
    activeScene = 0;

    QImage *imageObject = new QImage();
    QPixmap image;

    for(int i=0; i<ImageCount; i++){
        imageObject->load(fileNames.at(i));
        image = QPixmap::fromImage(*imageObject);
        sceneTab[i].addPixmap(image);
        sceneTab[i].setSceneRect(image.rect());
        PixmapTab[i] = image;
        historiqueTab[i].on_image_added(&PixmapTab[i]);
     }
    QGraphicsViewCustom **ExplorerPics  = new QGraphicsViewCustom*[uint(ImageCount)]; // création du tableau contenant les labels pour les images de 0+1 à i
    // chargement de l'image dans le Viewer

    SetMainPicture(&sceneTab[0], ui->PixFrame);
    SetMainPicture(&sceneTab[0], ui->carteMentale);
    SelectionMultiple.clear();
    SelectionMultiple.push_back(0);

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
        if(i == 0){
             ExplorerPics[i]->setStyleSheet("background: transparent; border: 2px solid blue");
        }


        connect(ExplorerPics[i], SIGNAL(mousePressed(const QPoint&)),this, SLOT(GetExplorerClick()));

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
    initImport = true;
    enableIfPic();
    delete [] ExplorerPics;
    ExplorerPics = nullptr;
    sceneInit = 1;
    zoom_value = 100.0;

//    colorFilter(QColor(150,0,0),150*3,QColor(0,0,150));
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
        historiqueTab[i].~Historique();
    }
    for(int i = 0; i< SelectionMultiple.size(); i++){
        ExplorerGraphicsView[SelectionMultiple.at(i)]->setStyleSheet("background: transparent; border: 0px");
    }

    while(ui->Layout_Explorer->count()>1){
        ui->Layout_Explorer->removeWidget(ui->Layout_Explorer->itemAt(1)->widget());
    }
   // ui->Layout_Explorer->addItem(new QSpacerItem(0,10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    for(int i = 0; i<ImageCount;i++)
        ExplorerGraphicsView[i] = nullptr;

    ImageCount = 0;
    sceneInit = 0;
    initImport = false;
    enableIfPic(false);
    sceneTab = nullptr;
    PixmapTab = nullptr;
    historiqueTab = nullptr;
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



void MainWindow::on_actionAnnuler_triggered(){
    int IDpix = ui->PixFrame->getID();
    historiqueTab[IDpix].on_actionUndo_triggered();
    PixmapTab[IDpix]=historiqueTab[ui->PixFrame->getID()].element;

    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->actionAnnuler->setEnabled(historiqueTab[ui->PixFrame->getID()].can_undo);
    ui->actionRetablir->setEnabled(historiqueTab[ui->PixFrame->getID()].can_redo);
}

void MainWindow::on_actionRetablir_triggered(){
    int IDpix = ui->PixFrame->getID();
    historiqueTab[IDpix].on_actionRedo_triggered();
    PixmapTab[IDpix]=historiqueTab[ui->PixFrame->getID()].element;

    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->actionAnnuler->setEnabled(historiqueTab[ui->PixFrame->getID()].can_undo);
    ui->actionRetablir->setEnabled(historiqueTab[ui->PixFrame->getID()].can_redo);
}

void MainWindow::update_historique(QPixmap *modification){
    historiqueTab[ui->PixFrame->getID()].on_newModification_added(modification);

    ui->actionAnnuler->setEnabled(historiqueTab[ui->PixFrame->getID()].can_undo);
    ui->actionRetablir->setEnabled(historiqueTab[ui->PixFrame->getID()].can_redo);
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

        update_historique(&PixmapTab[ui->PixFrame->getID()]);
    }

    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    qDebug() << __FUNCTION__ << "New size" << PixmapTab[IDpix].size().rwidth() << PixmapTab[IDpix].size().rheight();
}

void MainWindow::on_actionRogner_triggered()
{
    int IDpix = ui->PixFrame->getID();
    qDebug() << __FUNCTION__ << "Old size"  << PixmapTab[IDpix].size().rwidth() <<  PixmapTab[IDpix].size().rheight();

    int largeur = PixmapTab[IDpix].size().rwidth(),
        hauteur = PixmapTab[IDpix].size().rheight();
    Clip w_clip;
    rognageWindowOpen = true;
    ui->PixFrame->SelectCreer = false;
    w_clip.setLargeur(largeur);
    w_clip.setHauteur(hauteur);
    if (w_clip.exec()){
        largeur = w_clip.getLargeur();
        hauteur = w_clip.getHauteur();
        int x0=w_clip.getX0();
        int y0=w_clip.getY0();
        qDebug() << __FUNCTION__ << "clip to" <<x0 << y0<<largeur<<hauteur;
        sceneTab[IDpix].clear();
        sceneTab[IDpix].addPixmap(PixmapTab[IDpix].copy(x0,y0,largeur,hauteur));
        PixmapTab[IDpix] = PixmapTab[IDpix].copy(x0,y0,largeur,hauteur);

        update_historique(&PixmapTab[ui->PixFrame->getID()]);
    }
    qDebug() << "clip fermé, valeur openWindow" << w_clip.openWindow;
    if(w_clip.openWindow == true){
        rognageWindowOpen = true;
        w_clip.openWindow = false;
    }

    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);
    ExplorerGraphicsView[activeScene]->fitInView(sceneTab[activeScene].sceneRect(), Qt::KeepAspectRatio);
    qDebug() << __FUNCTION__ << "New size" << PixmapTab[IDpix].size().rwidth() << PixmapTab[IDpix].size().rheight();
}

void MainWindow::rognageGraphique(){
    double xb, yb, xe, ye;
    xb = ui->PixFrame->Xbegin;
    yb = ui->PixFrame->Ybegin;
    xe = ui->PixFrame->Xend;
    ye = ui->PixFrame->Yend;
    qDebug() << __FUNCTION__ << "clip to" <<xb << yb << xe << ye;
    sceneTab[activeScene].clear();
    sceneTab[activeScene].addPixmap(PixmapTab[activeScene].copy(xb,yb,xe-xb,ye-yb));
    PixmapTab[activeScene] = PixmapTab[activeScene].copy(xb,yb,xe-xb,ye-yb);
    sceneTab[activeScene].setSceneRect(PixmapTab[activeScene].rect());
    ui->PixFrame->fitInView(sceneTab[activeScene].sceneRect(),Qt::KeepAspectRatio);
    ExplorerGraphicsView[activeScene]->fitInView(sceneTab[activeScene].sceneRect(), Qt::KeepAspectRatio);

    update_historique(&PixmapTab[ui->PixFrame->getID()]);
}

void MainWindow::on_actionRotation_90_triggered()
// rotation à 90° du pixmap
{
    int IDpix = ui->PixFrame->getID();
    QTransform transform;

    transform.rotate(90);

    PixmapTab[IDpix] = PixmapTab[IDpix].transformed(transform);
    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);

    update_historique(&PixmapTab[ui->PixFrame->getID()]);
}

void MainWindow::on_actionRoation_90_triggered()
// rotation à -90° du pixmap
{
    int IDpix = ui->PixFrame->getID();
    QTransform transform;

    transform.rotate(-90);

    PixmapTab[IDpix] = PixmapTab[IDpix].transformed(transform);
    sceneTab[IDpix].clear();
    sceneTab[IDpix].addPixmap(PixmapTab[IDpix]);
    sceneTab[IDpix].setSceneRect(PixmapTab[IDpix].rect());
    ui->PixFrame->fitInView(sceneTab[IDpix].sceneRect(),Qt::KeepAspectRatio);

    update_historique(&PixmapTab[ui->PixFrame->getID()]);
}

void MainWindow::on_actionRotation_triggered()
{
    Rotate rotateWindow;    
    rotateWindow.setInfo(&PixmapTab[activeScene], &sceneTab[activeScene], ui->PixFrame);
    if (rotateWindow.exec())
    {}
    angleRotate = rotateWindow.getAngle();

    update_historique(&PixmapTab[ui->PixFrame->getID()]);
}



void MainWindow::on_actionNoir_et_Blanc_triggered()
{
    int id_pix = ui->PixFrame->getID();
    int largeur = PixmapTab[id_pix].size().rwidth(),
        hauteur = PixmapTab[id_pix].size().rheight();
    QImage im = PixmapTab[id_pix].toImage();
    QImage al = im.alphaChannel(); // Alpha à part
    for (int x = 0 ; x < largeur ; x++)
        for (int y = 0 ; y < hauteur ; y++)
        {
            int a = qAlpha(im.pixel(x,y));
            if (a > 0) // Ne modifie que si non transparent
            {
                int color = qGray(im.pixel(x,y));
                im.setPixel(x,y, qRgb(color,color,color));
                al.setPixel(x,y,a);
            }
        }

    im.setAlphaChannel(al);
    sceneTab[id_pix].clear();
    sceneTab[id_pix].addPixmap(QPixmap::fromImage(im));
    PixmapTab[id_pix] = QPixmap::fromImage(im);

    update_historique(&PixmapTab[ui->PixFrame->getID()]);
}

void MainWindow::on_actionCouleurs_triggered()
{
    ColorFilter cf;
    if (cf.exec())
    {
        QColor hue = cf.getHue();
        QColor to_filter = cf.getFilterColor();
        int thr = cf.getThreshold();
        colorFilter(to_filter,thr,hue);
    }
    update_historique(&PixmapTab[ui->PixFrame->getID()]);
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button_QuitSelectMode_clicked()
{
    Selection = false;
    SelecMode = 2; // rectangle par defaut
    ui->PixFrame->SelectCreer = false;
    sceneTab[activeScene].clear();
    sceneTab[activeScene].addPixmap(PixmapTab[activeScene]);
}

void MainWindow::on_Button_SelecRect_clicked()
{
    Selection = true;
    SelecMode = 2;
    qDebug() << "selection mode = " << SelecMode;
}

void MainWindow::on_Button_SelecEllipse_clicked()
{
    Selection = true;
    SelecMode = 1;
    qDebug() << "selection mode = " << SelecMode;
}

void MainWindow::on_Button_SelecTriangle_clicked()
{
    Selection = true;
    SelecMode = 0;
    qDebug() << "selection mode = " << SelecMode;
}
