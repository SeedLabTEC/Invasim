#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "Processor.h"

#define PREFIX_PU "/unit_"
#define SUFIX_PU ".json"

class ProcessorView : public QGraphicsView
{
    Q_OBJECT
public:
    ProcessorView(QWidget *parent, int x_dim, int y_dim, std::string working_dir);
    void start();
    QGraphicsScene* scene;
    Processor ** processors;
    int x_dim;
    int y_dim;
    std::string working_dir;

    void update_processors(unsigned int cycle, QVector<QColor> * ilet_colors_ptr);

//public slots:
};

#endif // SIMULATIONVIEW_H
