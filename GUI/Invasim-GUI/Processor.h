#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <ProcessorInfo.h>


#include <fstream>
#include "../../include/json.hpp"
using JSON = nlohmann::json;
#include <QDebug>

class Processor : public QGraphicsRectItem
{
public:
    Processor(QGraphicsItem *parent,int coo_x, int coo_y, std::string json_file);

    int coo_x;
    int coo_y;
    int ilet_id;
    int load;
    std::string state;
    std::string json_file;

    void change_color(QColor new_color);
    void update_data(unsigned int cycle);

    QGraphicsTextItem *json_data;
//public slots:
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PROCESSOR_H
