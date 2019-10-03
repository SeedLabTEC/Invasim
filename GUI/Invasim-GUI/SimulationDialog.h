#ifndef SIMULATIONDIALOG_H
#define SIMULATIONDIALOG_H

#include <QDialog>
#include <QAbstractButton>



namespace Ui {
class SimulationDialog;
}

class SimulationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulationDialog(QWidget *parent = nullptr);
    ~SimulationDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_clicked();

private:
    Ui::SimulationDialog *ui;
    bool applied = false;
    bool verify_directory_input();
    bool verify_proc_dimesion();
};

#endif // SIMULATIONDIALOG_H
