#include "ProcessorInfo.h"
#include "ui_ProcessorInfo.h"

ProcessorInfo::ProcessorInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessorInfo)
{
    ui->setupUi(this);
}

void ProcessorInfo::set_data(int coo_x, int coo_y, int ilet, int load, std::string state)
{
    this->ui->x_coo_label->setNum(coo_x);
    this->ui->y_coo_label->setNum(coo_y);
    if (ilet == -1)
    {
        this->ui->id_label->setText("None");
    }
    else
    {
        this->ui->id_label->setNum(ilet);
    }
    this->ui->load_label->setNum(load);
    this->ui->state_label->setText(state.c_str());
}

ProcessorInfo::~ProcessorInfo()
{
    delete ui;
}
