#include "connexionmenu.hpp"
#include "ui_connexionmenu.h"
#include "connection_screen.hpp"

ConnexionMenu::ConnexionMenu(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ConnexionMenu)
{
  ui->setupUi(this);
}

ConnexionMenu::~ConnexionMenu()
{
  delete ui;
}

void ConnexionMenu::on_SignIn_clicked()
{
    connection_screen * second_screen = new connection_screen(this);

    this->hide();
    second_screen->show();
}
