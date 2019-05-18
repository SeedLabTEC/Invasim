#include "ProcessorView.h"
#include <QDebug>

ProcessorView::ProcessorView(QWidget *parent) :
    QGraphicsView(parent)
{
    move(10,124);
    this->scene = new QGraphicsScene(0,0,1000,570);
    setScene(this->scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsRectItem* panel = new QGraphicsRectItem(0,0,1000,570);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    panel->setBrush(brush);
    panel->setOpacity(0.2);
    scene->addItem(panel);

    this->processors[0] = new Processor(NULL, 0, 0);
    this->processors[0]->setPos(0,0);
    scene->addItem(this->processors[0]);
    this->processors[0]->json_data = scene->addText("{}");

    this->processors[1] = new Processor(NULL, 0, 1);
    this->processors[1]->setPos(500,0);
    scene->addItem(this->processors[1]);
    this->processors[1]->json_data = scene->addText("{}");

    this->processors[2] = new Processor(NULL, 1, 0);
    this->processors[2]->setPos(0,285);
    scene->addItem(this->processors[2]);
    this->processors[2]->json_data = scene->addText("{}");

    this->processors[3] = new Processor(NULL, 1, 1);
    this->processors[3]->setPos(500,285);
    scene->addItem(this->processors[3]);
    this->processors[3]->json_data = scene->addText("{}");

}
