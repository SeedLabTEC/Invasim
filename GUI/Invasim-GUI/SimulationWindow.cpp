#include "SimulationWindow.h"
#include "ui_SimulationWindow.h"
#include <QDebug>
#include <QCloseEvent>
#include "StartView.h"
#include <stdio.h>

SimulationWindow::SimulationWindow(QWidget *parent,
                                   simulation_data *_current_sim_data,
                                   unsigned int max_cycle,
                                   bool is_loaded) :
    QWidget(parent),
    is_loaded(is_loaded),
    max_cycles(max_cycle),
    ui(new Ui::SimulationWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < MAX_COLORS; i++)
    {
          this->create_color();
    }

    this->current_sim_data = _current_sim_data;

    this->ui->x_label->setNum(this->current_sim_data->x_dim);
    this->ui->y_label->setNum(this->current_sim_data->y_dim);
    this->ui->probability_label->setNum(this->current_sim_data->decision);
    this->ui->seed_num_label->setNum(this->current_sim_data->seed);
    this->ui->dir_label->setText(this->current_sim_data->work_dir.c_str());


    if (!is_loaded)
    {
        this->env = new Environment(
                    this->current_sim_data->x_dim,
                    this->current_sim_data->y_dim,
                    float(this->current_sim_data->decision / float(100)),
                    this->current_sim_data->work_dir,
                    this->current_sim_data->seed);
        this->env->start_environment();
        this->env->step(2);
    }

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
    QMessageBox::StandardButton exit_btn = QMessageBox::question( this, "Invasim",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (exit_btn != QMessageBox::Yes)
    {
        event->ignore();
    }
    else
    {
        QMessageBox::StandardButton save_btn = QMessageBox::question( this, "Invasim",
                                                                    tr("Do you want to save?\n"),
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if(save_btn != QMessageBox::Yes)
        {
            std::string del_command = "rm -f ";
            del_command.append(this->current_sim_data->work_dir);
            del_command.append("/*.json");
            system(del_command.c_str());
        }
        event->accept();

    }
}

void SimulationWindow::step_one()
{
    this->processor_view->update_processors(this->cycle, &this->ilet_colors);
    if(!is_loaded)
    {
        this->env->step(1);
        this->cycle++;
    }
    else
    {
        if(this->cycle < (this->max_cycles - 1))
        {
            this->cycle++;
            std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_SEC));
        }
        else
            this->sim_ended = true;
    }

    if(this->sim_ended)
    {
        QMessageBox::warning(
                    this,
                    "Warning",
                    "Simulation is ended!");
    }

    this->verify_ilet_colors();
}


void SimulationWindow::on_pushButton_released()
{
    this->ui->pushButton->setEnabled(false);
    this->step_one();
    this->ui->pushButton->setEnabled(true);

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
    IletsView *diag = new IletsView(this, this->current_sim_data->work_dir);
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

void SimulationWindow::on_pushButton_3_released()
{
    MemoryView *diagMem = new MemoryView(this, this->current_sim_data->work_dir);
    diagMem->setModal(true);
    diagMem->exec();
    delete diagMem;

}
