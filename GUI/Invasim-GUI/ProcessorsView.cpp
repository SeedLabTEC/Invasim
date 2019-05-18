#include "ProcessorView.h"
#include <QDebug>

ProcessorView::ProcessorView(QWidget *parent, int x_dim, int y_dim, std::string working_dir) :
    QGraphicsView(parent),
    x_dim(x_dim),
    y_dim(y_dim),
    working_dir(working_dir)
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

    this->processors = new Processor *[x_dim * y_dim];

    int index = 1;
    for (int i = 0; i < x_dim; i++) {
        for (int j = 0; j < y_dim; j++) {
            std::string tmp = working_dir;
            tmp.append(PREFIX_PU);
            tmp.append(std::to_string(index));
            tmp.append(SUFIX_PU);
            this->processors[index - 1] = new Processor(NULL, i, j, tmp);
            this->processors[index - 1]->setPos(j*60, i*60);
            scene->addItem(this->processors[index - 1]);
            this->processors[index - 1]->json_data = scene->addText("{}");
            this->processors[index - 1]->json_data->setPos(j*60, i*60);
            index++;
        }
    }
}

void ProcessorView::update_processors(unsigned int cycle)
{
    int size_procs = this->x_dim * this->y_dim;
    for (int i = 0; i < size_procs; i++) {
        this->processors[i]->update_data(cycle);
    }
}
