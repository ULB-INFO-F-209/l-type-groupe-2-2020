#include "main_menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_menu w;
    w.show();
    return a.exec();
}
