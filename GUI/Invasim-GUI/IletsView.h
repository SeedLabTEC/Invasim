#ifndef ILETSVIEW_H
#define ILETSVIEW_H

#include <QDialog>
#include <QStandardItemModel>
#include <fstream>

#include "../../include/json.hpp"
using JSON = nlohmann::json;

namespace Ui {
class IletsView;
}

class IletsView : public QDialog
{
    Q_OBJECT

public:
    explicit IletsView(QWidget *parent = nullptr, std::string _working_dir = ".");
    std::string working_dir;
    ~IletsView();

private:
    Ui::IletsView *ui;
};

#endif // ILETSVIEW_H
