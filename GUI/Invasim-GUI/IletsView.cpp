#include "IletsView.h"
#include "ui_IletsView.h"

IletsView::IletsView(QWidget *parent, std::string working_dir) :
    QDialog(parent),
    working_dir(working_dir),
    ui(new Ui::IletsView)
{
    ui->setupUi(this);

    std::string line;
    working_dir.append("/ilets.json");
    std::ifstream r_file(working_dir);
    std::getline(r_file, line);
    r_file.close();
    JSON ilets_json = JSON::parse(line);

    QStandardItemModel* model = new QStandardItemModel();

    foreach (JSON ilet, ilets_json) {
       int id = ilet["Id"];
       QStandardItem* item_ilet = new QStandardItem(QString("ID = %0").arg(id));
       foreach (JSON operation, ilet["Operations"]) {
           int param = operation["Parameter"];
           std::string op = operation["Operation"];
           QStandardItem* item_op = new QStandardItem(QString("%0").arg(op.c_str()));
           QStandardItem* item_param = new QStandardItem(QString("%0").arg(param));
           item_ilet->appendRow(item_op);
           item_op->appendRow(item_param);
       }
       model->appendRow(item_ilet);
    }




    this->ui->ilets_tree->setModel(model);
}

IletsView::~IletsView()
{
    delete ui;
}
