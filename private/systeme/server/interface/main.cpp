#include "Interface.hpp"
#include "parsing.hpp"
#include "screen.hpp"
#include "Menu.hpp"

using namespace Parsing;

int main(int argc, char const *argv[])
{
	/*std::string choix[6] = {"Friends list", "Friends requests", "Add friend",
								"Remove friend", "Back"};
	std::string cn[3] = {"Sign in", "Sign up", "Quit"};
	Interface win{};
	char p[20]; char m[20];
	char e[] = "Your pseudo is already taken!";
	char pseudo[] = "Aissa2024",p2[] = "H3LIN_92",p3[] = "UMLx34D",
		p4[] = "la_blgs_du_78", p5[] = "4Junior4", p6[]="lalaMSP",
		p7[] = "Derboise", p8[] = "Bob_eponge", p9[] = "ZaNiLiA",
		p10[] = "__DILRABA__", p11[] = "LOLAMNP", p12[]= "San_goku_3",
		p13[] = "WejXden", p14[] = "xXsandraXx", p15[] = "Park_Hyung_Sik3",
		p16[] = "Jay12Park";
	Profile prof(pseudo, 444522), prof2(p2, 20), prof3(p3, 892642),
			prof4(p4, 871), prof5(p5, 56291), prof6(p6, 0), 
			prof7(p7, 4251),  prof8(p8, 12),  prof9(p9, 1),
			prof10(p10, 10000), prof11(p11, 5710), prof12(p12, 34100),
			prof13(p13,718), prof14(p14,78143), prof15(p15,81655), prof16(p16,9021);

	std::vector<Profile*> v = {&prof, &prof2, &prof3, &prof4,&prof5, &prof6,
							&prof7,&prof8,&prof9,&prof10,&prof11,&prof12,&prof13,
							&prof14, &prof15,&prof16};
	//win.print_profile(v, REQ);
	//win.set_screen(&HOME_TITLE,&HOME_SAYING, nullptr, nullptr);

	//win.get_connexion(p, m, NO_ERROR, S_IN);	

	//win.get_pseudo(p, NO_ERROR, DEL);	

	//win.print_menu(3,cn, HOME);	*/

	Menu m{};
	m.start_session();
	return 0;
}


