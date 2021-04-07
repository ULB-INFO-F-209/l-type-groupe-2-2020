#include "connection_screen.hpp"
#include "ui_connection_screen.h"

connection_screen::connection_screen(QWidget *parent) :
  QMainWindow(parent),prec(parent),
  ui(new Ui::connection_screen)
{
  ui->setupUi(this);
}

connection_screen::~connection_screen()
{
  delete ui;
}


void connection_screen::on_quit_button_clicked()
{
  this->hide();
  prec->show();
}
