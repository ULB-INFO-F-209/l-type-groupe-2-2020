#include "Interface.hpp"

int main(int argc, char const *argv[])
{
	Interface win{};
	std::string choix[3] ={"Aissa", "Helin", "Imane"};
	win.print_menu(3,choix);
	return 0;
}

