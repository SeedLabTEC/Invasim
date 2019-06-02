#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <qmessagebox.h>
#include <IletsView.h>

#include "ProcessorView.h"
#include "../../include/Environment.h"


struct simulation_data {
    std::string work_dir;
    int x_dim;
    int y_dim;
    int decision;
    int seed;
    bool is_set;
};

namespace Ui {
class SimulationWindow;
}

class SimulationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWindow(QWidget *parent = nullptr,
                              simulation_data *_current_sim_data = nullptr,
                              unsigned int max_cycle = 10,
                              bool is_loaded = false);
    ~SimulationWindow();

    simulation_data *current_sim_data;
    ProcessorView *processor_view;
    Environment *env;
    void closeEvent (QCloseEvent *event);

    unsigned int cycle = 0;
    QVector<QColor> ilet_colors;
    double current_hue = double(0.0);


private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    bool is_loaded;
    bool sim_ended = false;
    unsigned int max_cycles;
    Ui::SimulationWindow *ui;
    void verify_ilet_colors();
    void create_color();
    void step_one();
};

#endif // SIMULATIONWINDOW_H
