#include "ProcessorView.h"
#include <QDebug>

ProcessorView::ProcessorView(QWidget *parent, int x_dim, int y_dim, std::string working_dir) :
    QGraphicsView(parent),
    x_dim(x_dim),
    y_dim(y_dim),
    working_dir(working_dir)
{
    move(10,124);
    this->scene = new QGraphicsScene(0,0,1001,571);
    setScene(this->scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QGraphicsRectItem* panel = new QGraphicsRectItem(0,0,1001,571);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    panel->setBrush(brush);
    panel->setOpacity(0.2);
    scene->addItem(panel);

    this->processors = new Processor *[x_dim * y_dim];
    int height = 1000 / y_dim;
    int width = 570 /  x_dim;

    int index = 1;
    for (int i = 0; i < x_dim; i++) {
        for (int j = 0; j < y_dim; j++) {
            std::string tmp = working_dir;
            tmp.append(PREFIX_PU);
            tmp.append(std::to_string(index));
            tmp.append(SUFIX_PU);



            this->processors[index - 1] = new Processor(NULL, i, j, tmp, height - 1, width - 1);
            this->processors[index - 1]->setPos(j*height, i*width);
            scene->addItem(this->processors[index - 1]);
            if (height >= 30 && width >= 30)
            {
                this->processors[index - 1]->json_data = scene->addText("N/A");
                this->processors[index - 1]->json_data->setPos(j*height, i*width);
            }
            index++;
        }
    }
}

void ProcessorView::update_processors(unsigned int cycle, QVector<QColor> * ilet_colors_ptr)
{
    int size_procs = this->x_dim * this->y_dim;
    for (int i = 0; i < size_procs; i++) {
        this->processors[i]->update_data(cycle);
        this->processors[i]->update_color(ilet_colors_ptr);
    }
}
