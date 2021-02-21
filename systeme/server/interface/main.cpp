#include "Interface.hpp"

int main(int argc, char const *argv[])
{
	Interface win{};
	std::string choix[3] ={"Aissa", "Helin", "Imane"};
	char p[20]; char m[20];
	win.get_connexion(p,m,NULL);

	return 0;
}
