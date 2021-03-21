#include "interfaceGui.h"

//using namespace Ui;

Ui::InterafaceGui::InterafaceGui():
QMainWindow(nullptr),ui(new Ui_InterafaceGui) {
    ui->setupUi(this);
    show();
}

Ui::InterafaceGui::~InterafaceGui(){
    delete ui;
}