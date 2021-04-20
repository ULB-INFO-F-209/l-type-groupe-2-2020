#include "main_menu.h"
#include "ui_main_menu.h"

Main_menu::Main_menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Main_menu)
{
    ui->setupUi(this);
}

Main_menu::~Main_menu()
{
    delete ui;
}

