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

    for (int i = 0; i < 10; i++)
    {
          this->create_color();
    }

    this->current_sim_data = _current_sim_data;

    this->ui->x_label->setNum(this->current_sim_data->x_dim);
    this->ui->y_label->setNum(this->current_sim_data->y_dim);
    this->ui->probability_label->setNum(this->current_sim_data->decision);
    this->ui->seed_num_label->setNum(this->current_sim_data->seed);
    this->ui->dir_label->setText(this->current_sim_data->work_dir.c_str());

    this->env = new Environment(
                this->current_sim_data->x_dim,
                this->current_sim_data->y_dim,
                float(this->current_sim_data->decision / float(100)),
                this->current_sim_data->work_dir,
                this->current_sim_data->seed);
    this->env->start_environment();
    this->env->step(2);

    this->processor_view = new ProcessorView(this,
                                             this->current_sim_data->x_dim,
                                             this->current_sim_data->y_dim,
                                             this->current_sim_data->work_dir);
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
        std::string del_command = "rm -f ";
        del_command.append(this->current_sim_data->work_dir);
        del_command.append("/*.json");
        system(del_command.c_str());
        event->accept();
    }
}

void SimulationWindow::on_pushButton_released()
{
    this->ui->pushButton->setEnabled(false);
    this->processor_view->update_processors(this->cycle, &this->ilet_colors);
    this->ui->pushButton->setEnabled(true);
    this->env->step(1);
    this->cycle++;
    this->verify_ilet_colors();
}

void SimulationWindow::verify_ilet_colors()
{
    std::string line;
    std::string  working_dir = this->current_sim_data->work_dir;
    working_dir.append("/ilets.json");
    std::ifstream r_file(working_dir);
    std::getline(r_file, line);
    r_file.close();
    JSON ilets_json = JSON::parse(line);
    if(ilets_json.size() > this->ilet_colors.size())
        this->create_color();
}

void SimulationWindow::on_pushButton_2_released()
{
    IletsView *diag = new IletsView(this);
    diag->working_dir = this->current_sim_data->work_dir;
    diag->setModal(true);
    diag->exec();
    delete diag;
}

void SimulationWindow::create_color()
{
    this->ilet_colors.push_back( QColor::fromHslF(current_hue, 1.0, 0.5) );
    current_hue += 0.618033988749895;
    current_hue = std::fmod(current_hue, 1.0);
}
