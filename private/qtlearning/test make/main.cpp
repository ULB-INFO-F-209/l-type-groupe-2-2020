#include <iostream>
#include <QApplication>
#include "Button.hpp"
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Button bouton("Test", 3);
    bouton.show();
 
    return app.exec();
}