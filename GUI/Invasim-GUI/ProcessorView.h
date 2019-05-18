#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "Processor.h"

class ProcessorView : public QGraphicsView
{
    Q_OBJECT
public:
    ProcessorView(QWidget *parent);
    void start();
    QGraphicsScene* scene;
    Processor * processors[4];

//public slots:
};

#endif // SIMULATIONVIEW_H
