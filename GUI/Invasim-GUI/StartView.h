#ifndef STARTVIEW_H
#define STARTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QCoreApplication>
#include <string.h>

#include "SimulationDialog.h"
#include "SimulationWindow.h"

namespace Ui {
class StartView;
}

class StartView : public QWidget
{
    Q_OBJECT

public:
    explicit StartView(QWidget *parent = nullptr);
    ~StartView();

    simulation_data get_simulation_data();
    void set_simulation_data(std::string _dir, int _x_dim, int _y_dim, int _decision, int _seed);

public slots:
    void start_simulation();

private:
    Ui::StartView *ui;
    QPushButton *m_button;
    simulation_data sim_data;
};

#endif // STARTVIEW_H
