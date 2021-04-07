#include "InterfaceGUI.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  InterfaceGUI w;
  w.show();

  return a.exec();
}
