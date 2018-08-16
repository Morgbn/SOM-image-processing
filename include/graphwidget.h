#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H
/** @file graphwidget.h
    Sous classe de QGraphicsView
*/

#include <QGraphicsView>

/**
 * Là est où est affiché les images
 * Ajoute à QGraphicsView la possibilité de zoomer
 * @param parent parent
 */
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * Constructeur de la classe GraphWidget
     * @param parent parent
     */
    GraphWidget(QWidget *parent = 0);

public slots:
    /**
     * Zoom avant
     */
    void zoomIn();
    /**
     * Zoom arrière
     */
    void zoomOut();

protected:
    /**
     * Gestion évenement molette souris
     * @param event évenement molette souris
     */
    void wheelEvent(QWheelEvent *event);
    /**
     * Changer l'échelle de la vue
     * @param scaleFactor facteur d'agrandissement
     */
    void scaleView(qreal scaleFactor);
};


#endif // GRAPHWIDGET_H
