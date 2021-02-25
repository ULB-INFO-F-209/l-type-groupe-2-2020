#include "test.hpp"

namespace Test{
	//testing 1 : A supprimer 
	std::string pseudo = "Aissa2024",moi = "Yang_Mi",p2 = "H3LIN_92",p3 = "UMLx34D",
		p4 = "la_blgs_du_78", p5 = "4Junior4", p6="lalaMSP",
		p7 = "Derboise", p8 = "Bob_eponge", p9 = "ZaNiLiA",
		p10 = "__DILRABA__", p11 = "LOLAMNP", p12= "San_goku_3",
		p13 = "WejXden", p14 = "xXsandraXx", p15 = "Park_Hyung_Sik3",
		p16 = "Jay12Park", other = "Alicia45";
	
		Profile prof(pseudo.c_str(), 444522), prof2(p2.c_str(), 20), prof3(p3.c_str(), 892642),
			prof4(p4.c_str(), 871), prof5(p5.c_str(), 56291), prof6(p6.c_str(), 0), 
			prof7(p7.c_str(), 4251),  prof8(p8.c_str(), 12),  prof9(p9.c_str(), 1),
			prof10(p10.c_str(), 10000), prof11(p11.c_str(), 5710), prof12(p12.c_str(), 34100),
			prof13(p13.c_str(),718), prof14(p14.c_str(),78143), prof15(p15.c_str(),81655), prof16(p16.c_str(),9021),
			mon_prof(moi.c_str(), 21890), other_prof(other.c_str(), 45);
	
	std::vector<Profile*> vect = {&prof, &prof2, &prof3, &prof4,&prof5, &prof6,
							&prof7,&prof8,&prof9,&prof10,&prof11,&prof12,&prof13,
							&prof14, &prof15,&prof16};
}
