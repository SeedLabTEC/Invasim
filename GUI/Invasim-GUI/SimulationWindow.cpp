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
    std::string line;
    std::ifstream r_file("/home/dennis/invasim_data/unit_1.json");
    std::getline(r_file, line);
    r_file.close();
    JSON old = JSON::parse(line);
    std::string data_w = old[this->cycle].dump(2);
    this->processor_view->processors[0]->json_data->setPlainText(data_w.c_str());
    this->processor_view->processors[0]->json_data->setPos(0,0);


    line.clear();
    r_file = std::ifstream("/home/dennis/invasim_data/unit_2.json");
    std::getline(r_file, line);
    r_file.close();
    old = JSON::parse(line);
    data_w = old[this->cycle].dump(2);
    this->processor_view->processors[1]->json_data->setPlainText(data_w.c_str());
    this->processor_view->processors[1]->json_data->setPos(590, 0);


    line.clear();
    r_file = std::ifstream("/home/dennis/invasim_data/unit_3.json");
    std::getline(r_file, line);
    r_file.close();
    old = JSON::parse(line);
    data_w = old[this->cycle].dump(2);
    this->processor_view->processors[2]->json_data->setPlainText(data_w.c_str());
    this->processor_view->processors[2]->json_data->setPos(0, 280);

    line.clear();
    r_file = std::ifstream("/home/dennis/invasim_data/unit_4.json");
    std::getline(r_file, line);
    r_file.close();
    old = JSON::parse(line);
    data_w = old[this->cycle].dump(2);
    this->processor_view->processors[3]->json_data->setPlainText(data_w.c_str());
    this->processor_view->processors[3]->json_data->setPos(590, 280);

    this->ui->pushButton->setEnabled(true);
    this->env->step(1);
    this->cycle++;
}
