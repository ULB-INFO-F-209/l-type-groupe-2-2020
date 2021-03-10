#include <iostream>
#include <vector>
#include "parsing.hpp"

using namespace Parsing;

int main(int argc, char const *argv[])
{
	char buffer[] = "Luo_lunxi|8927" ;
	Profile prof{};
	profile_from_str(buffer,&prof);
	std::cout << "pseudo  : "<<prof.pseudo<<std::endl;
	std::cout << "score  : "<<prof.score<<std::endl;

	/*std::vector<Profile> res{};
	profile_list_from_str(buffer, &res);
	for(auto p:res){
		std::cout<<"pseudo "<<p.pseudo<< " | score "<<p.score<<std::endl;
	}*/
	return 0;
}