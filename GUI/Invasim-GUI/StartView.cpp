#include "StartView.h"
#include "ui_StartView.h"

StartView::StartView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartView)
{
    ui->setupUi(this);

    this->sim_data.is_set = false;

    connect(this->ui->simulate_button, SIGNAL (released()), this, SLOT (start_simulation()));

}

StartView::~StartView()
{
    delete ui;
}

simulation_data StartView::get_simulation_data()
{
    return this->sim_data;
}

void StartView::set_simulation_data(std::string _dir, int _x_dim, int _y_dim, int _decision, int _seed)
{
    this->sim_data.work_dir = _dir;
    this->sim_data.x_dim = _x_dim;
    this->sim_data.y_dim = _y_dim;
    this->sim_data.decision = _decision;
    this->sim_data.seed = _seed;
    this->sim_data.is_set = true;
}

void StartView::start_simulation()
{
    SimulationDialog *diag = new SimulationDialog(this);
    diag->setModal(true);
    this->hide();
    diag->exec();
    delete diag;
    this->show();
    if (this->sim_data.is_set)
    {
        SimulationWindow *new_window = new SimulationWindow(NULL, &this->sim_data);
        this->showMinimized();
        new_window->show();
        this->sim_data.is_set = false;
    }
}
