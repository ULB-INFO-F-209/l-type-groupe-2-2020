#include "getplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GetPlayer w;
    w.show();
    return a.exec();
}
