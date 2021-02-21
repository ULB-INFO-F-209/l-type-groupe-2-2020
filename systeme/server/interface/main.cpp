#include "Interface.hpp"
#include "parsing.hpp"

using namespace Parsing;


int main(int argc, char const *argv[])
{
	Interface win{};
	std::string choix[3] ={"Aissa", "Helin", "Imane"};
	char p[20]; char m[20];
	char e[] = "Your pseudo is already taked!";
	char pseudo[] = "Aissa2024";
	char p2[] = "H3LIN_92";
	char p3[] = "UMLx34D";
	char p4[] = "la_blgs_du_78";
	Profile prof(pseudo, 444522);
	Profile prof2(p2, 20);
	Profile prof3(p3, 892642);
	Profile prof4(p4, 871);

	std::vector<Profile*> v = {&prof, &prof2, &prof3, &prof4};
	
	win.print_profile(v);

	return 0;
}
