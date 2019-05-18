#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QGraphicsRectItem>
#include <QGraphicsView>

class Processor : public QGraphicsRectItem
{
public:
    Processor(QGraphicsItem *parent,int coo_x, int coo_y);

    int coo_x;
    int coo_y;

    QGraphicsTextItem *json_data;
//public slots:

};

#endif // PROCESSOR_H
