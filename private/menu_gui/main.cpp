#include "interfaceGui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Ui::InterafaceGui w{};
    //w.show();

    return app.exec();
}