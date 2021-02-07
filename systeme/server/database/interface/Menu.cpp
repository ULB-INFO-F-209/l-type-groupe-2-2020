#include "Menu.hpp"

//________________________MENU_ABSTRACT____________________________

//constructor
Menu::Menu(const std::initializer_list<std::string>& init)noexcept : 
_size(init.size()), _choices(new std::string[_size]){
	const std::string* p = init.begin();
	ptrdiff_t max = static_cast<ptrdiff_t>(_size);
	for (ptrdiff_t i = 0; i < max; ++i){
		_choices[i] = p[i];	
	}
}
//getters
const void Menu::get_user_choice(){
	int res; 
	std::cout<< "Votre choix >> ";
	std::cin>> res;
	while(res <= 0 && res > static_cast<int>(_size)){
		std::cout<<"choix non valide"<<std::endl;
		std::cout<< "Entrez un choix valide >> ";
		std::cin>> res;
	}
	//executer la commande 
	execute_choice(res);
}

//affichage
void Menu::_dsp (std::ostream& out) const{
	for (size_t i = 0; i < _size; ++i){
		out << i+1 << " "<<_choices[i]<<std::endl;
	}
}

//destructor
Menu::~Menu() noexcept{delete[] _choices;};
