#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Interface)
{
    ui->setupUi(this);
}

Interface::~Interface()
{
    delete ui;
}


void Interface::on_signIn_clicked()
{
    int x = 10+3;
}
