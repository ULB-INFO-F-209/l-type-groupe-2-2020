#include "MenuGui.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MenuGui m;
	m.start_session();
	return  a.exec();
}