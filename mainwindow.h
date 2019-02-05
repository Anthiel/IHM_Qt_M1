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

/*!
 * \class MainWindow
 * \brief Fenêtre principale du projet
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int activeScene = 0;

    /*!
     * Vrai si la scène est initialisée.
     * Faux sinon.
     */
    bool sceneInit = 0;
    QGraphicsSceneCustom *sceneTab;
    QPixmap* PixmapTab;
    QGraphicsProxyWidget* proxyPixmapTab;
    QGraphicsView* view;
    int angleRotate = 0;
    int spacing = 25;
    QGraphicsViewCustom *ExplorerGraphicsView[200];

    /*!
     * Nombre d'images chargées
     */
    int ImageCount=0;
    bool rognageWindowOpen = false;
    QGraphicsRectItem* itemRognage;
    QPainter *painter;
    double zoom_value;


private slots:

    /*!
     * \brief Fonction d'import d'images.
     */
    void on_actionImporter_triggered();

    /*!
     * \brief Enlève toutes les images chargées.
     */
    void on_actionTout_supprimer_triggered();

    /*!
     * \brief Redimension de l'image en cours (fenêtre de réglages).
     */
    void on_actionRedimensionner_triggered();

    /*!
     * \brief Rognage de l'image en cours (fenêtre de réglages).
     */
    void on_actionRogner_triggered();

    /*!
     * \brief Sauvegarde des modifications de l'image en cours.
     */
    void on_actionExporter_l_image_triggered();

    /*!
     * \brief Rotation horaire à 90° de l'image en cours.
     */
    void on_actionRotation_90_triggered();

    /*!
     * \brief Rotation antihoraire à 90° de l'image en cours.
     */
    void on_actionRoation_90_triggered();

    /*!
     * \brief Rotation de l'image en cours (fenêtre de réglages).
     */
    void on_actionRotation_triggered();

    /*!
     * \brief Filtre noir et blanc sur l'image en cours.
     */
    void on_actionNoir_et_Blanc_triggered();

    /*!
     * \brief Fenêtre "remininder".
     * \param event
     */
    void closeEvent(QCloseEvent *event);


public slots :
    void GetExplorerClick();
    void ClickOnFrame();

protected:
    void wheelEvent(QWheelEvent* e);

private:
    /*!
     * \brief Dé.grise des options en fonction du chargement de l'image.
     * \param enable (true dégrise et false grise)
     */
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
    void drawRectSelection(double xb, double yb,double xe, double ye);
    void updateSelectionPoint(int xb, int yb, int xe, int ye);
    void PoignetUpdate();

    /*!
     * \brief Selectionne selon la couleur passée sur l'image
     * \param color, couleur de référence
     * \param thr, seuil de tolérance
     * \return Un tableau de booléen de taille largeur*hauteur de l'image
     *         avec en true les pixels selectionnés.
     */
    bool* selectByColor(QColor color, uint thr);

    /*!
     * \brief Zoom sur l'image en cours.
     * \param z_ratio Taille du zoom
     */
    void zoom(double z_ratio);
};

#endif // MAINWINDOW_H
