#ifndef PROCESSORINFO_H
#define PROCESSORINFO_H

#include <QDialog>

namespace Ui {
class ProcessorInfo;
}

class ProcessorInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessorInfo(QWidget *parent = nullptr);
    void set_data(int coo_x, int coo_y, int ilet, int load, std::string state);
    ~ProcessorInfo();

private:
    Ui::ProcessorInfo *ui;
};

#endif // PROCESSORINFO_H
