#include "Menu.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Menu m;
	m.start_session();
	return  a.exec();
}