#include "MemoryView.h"
#include "ui_MemoryView.h"
#include <QDebug>

MemoryView::MemoryView(QWidget *parent, std::string _working_dir) :
    QDialog(parent),
    working_dir(_working_dir),
    ui(new Ui::MemoryView)
{
    ui->setupUi(this);

    std::string line;
    working_dir.append("/memory.json");
    std::ifstream r_file(working_dir);
    std::getline(r_file, line);
    r_file.close();
    JSON mem = JSON::parse(line);
    tableMemHeader<<"Address"<<"Value";

    ui->tableMem1->setHorizontalHeaderLabels(tableMemHeader);
    ui->tableMem2->setHorizontalHeaderLabels(tableMemHeader);
    ui->tableMem3->setHorizontalHeaderLabels(tableMemHeader);
    ui->tableMem4->setHorizontalHeaderLabels(tableMemHeader);

    ui->tableMem1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMem2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMem3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableMem4->setSelectionBehavior(QAbstractItemView::SelectRows);


    ui->tableMem1->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableMem2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableMem3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableMem4->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableMem1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMem2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMem3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableMem4->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int j;
    int dataMem;
    JSON json_info;
    for(int i = 0; i<4 ; i++) {
        json_info = mem[i];
        j = 0;
        foreach(JSON data, json_info){
            dataMem = data["data"];
            switch (i) {
                case 0:
                    ui->tableMem1->setItem(j, 0, new QTableWidgetItem(QString::number(j)));
                    ui->tableMem1->setItem(j, 1, new QTableWidgetItem(QString::number(dataMem)));
                    break;
                case 1:
                    ui->tableMem2->setItem(j, 0, new QTableWidgetItem(QString::number(j)));
                    ui->tableMem2->setItem(j, 1, new QTableWidgetItem(QString::number(dataMem)));
                    break;
                case 2:
                    ui->tableMem3->setItem(j, 0, new QTableWidgetItem(QString::number(j)));
                    ui->tableMem3->setItem(j, 1, new QTableWidgetItem(QString::number(dataMem)));
                    break;
                case 3:
                    ui->tableMem4->setItem(j, 0, new QTableWidgetItem(QString::number(j)));
                    ui->tableMem4->setItem(j, 1, new QTableWidgetItem(QString::number(dataMem)));
                    break;

                default:
                    break;
            }
            j++;
        }
    }

}

MemoryView::~MemoryView()
{
    delete ui;
}

