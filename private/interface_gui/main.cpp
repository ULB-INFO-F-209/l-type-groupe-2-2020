#include "connexionmenu.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ConnexionMenu w;
  w.show();

  return a.exec();
}
