#include "Processor.h"
#include <QBrush>

Processor::Processor(QGraphicsItem *parent, int coo_x, int coo_y) :
    QGraphicsRectItem(parent),
    coo_x(coo_x),
    coo_y(coo_y)
{
    setRect(0,0,495,280);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::color0);
    setBrush(brush);
}
