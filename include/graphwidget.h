#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void wheelEvent(QWheelEvent *event);
    void scaleView(qreal scaleFactor);
};


#endif // GRAPHWIDGET_H
