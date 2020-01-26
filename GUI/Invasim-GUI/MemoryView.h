#ifndef MEMORYVIEW_H
#define MEMORYVIEW_H

#include <QDialog>
#include <QStandardItemModel>
#include <fstream>

#include "../../include/json.hpp"
using JSON = nlohmann::json;

namespace Ui {
class MemoryView;
}

class MemoryView : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryView(QWidget *parent = nullptr, std::string _working_dir = ".");
    std::string working_dir;
    ~MemoryView();

private:
    Ui::MemoryView *ui;
    QStringList tableMemHeader;
};

#endif // MEMORYVIEW_H
