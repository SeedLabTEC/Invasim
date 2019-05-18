#include "SimulationWindow.h"
#include "ui_SimulationWindow.h"
#include <QDebug>
#include <QCloseEvent>
#include "StartView.h"

SimulationWindow::SimulationWindow(QWidget *parent, simulation_data *_current_sim_data) :
    QWidget(parent),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);
    this->current_sim_data = _current_sim_data;

    this->env = new Environment(
                this->current_sim_data->x_dim,
                this->current_sim_data->y_dim,
                float(this->current_sim_data->decision / float(100)),
                this->current_sim_data->work_dir,
                this->current_sim_data->seed);
    this->env->start_environment();
    this->env->step(1);

    this->processor_view = new ProcessorView(this);
    this->processor_view->show();
}

SimulationWindow::~SimulationWindow()
{
    delete ui;
}

void SimulationWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Invasim",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

void SimulationWindow::on_pushButton_released()
{
    this->ui->pushButton->setEnabled(false);

    for (int i = 0; i < 4; i++)
    {
        this->processor_view->processors[i]->update_data(this->cycle);

    }

    this->ui->pushButton->setEnabled(true);
    this->env->step(1);
    this->cycle++;
}
