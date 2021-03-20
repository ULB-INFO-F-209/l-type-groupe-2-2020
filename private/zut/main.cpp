#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QWidget w;
    w.show();
    return app.exec();
}