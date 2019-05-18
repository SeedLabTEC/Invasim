#include "SimulationDialog.h"
#include "ui_SimulationDialog.h"

#include <QDebug>
#include <QMessageBox>
#include "StartView.h"

SimulationDialog::SimulationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulationDialog)
{
    ui->setupUi(this);
}

SimulationDialog::~SimulationDialog()
{
    delete ui;
}

bool SimulationDialog::verify_directory_input()
{
    bool success = false;
    if (this->ui->dir_input->toPlainText().length() != 0)
        success = true;
    return success;
}

bool SimulationDialog::verify_proc_dimesion()
{
    bool success = false;
    if (this->ui->x_input->value() * this->ui->y_input->value() <= 100)
        success = true;
    return success;
}


void SimulationDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text() == "Apply")
    {
        bool proc_correct = this->verify_proc_dimesion();
        bool dir_correct = this->verify_directory_input();
        if (proc_correct && dir_correct)
        {
            StartView *start = dynamic_cast<StartView *>(this->parent());

            start->set_simulation_data(
                        this->ui->dir_input->toPlainText().toStdString(),
                        this->ui->x_input->value(),
                        this->ui->y_input->value(),
                        this->ui->decision_input->value(),
                        this->ui->seed_input->value());
            this->applied = true;
        }
        if (!dir_correct)
        {
            QMessageBox::critical(
                        this,
                        "Error",
                        "Directory is empty");
        }
        if (!proc_correct)
        {
            QMessageBox::critical(
                        this,
                        "Error",
                        "Max amount of processors exceed");
        }

    } else if (button->text() == "&OK") {
        if (!this->applied)
        {
            QMessageBox::critical(
                        this,
                        "Error",
                        "Changes were not applied");
        }
    }
}
