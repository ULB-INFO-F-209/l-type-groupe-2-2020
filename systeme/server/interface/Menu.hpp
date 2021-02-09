#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
#include <cstring>
#include <ncurses.h>

class Menu{
	size_t _size;
	std::string *_choices; 
public:
	//constructeur
	explicit Menu(const std::initializer_list<std::string>& init)noexcept : 
	_size(init.size()), _choices(new std::string[_size]){
		const std::string* p = init.begin();
		ptrdiff_t max = static_cast<ptrdiff_t>(_size);
		for (ptrdiff_t i = 0; i < max; ++i){
			_choices[i] = p[i];	
		}
	}
	
	//getters 
	virtual const void get_user_choice(){}
	virtual void print(WINDOW *win){
		int y = 3, x = 20;
		for (size_t i = 0; i < _size; ++i)
		{
			char cstr[_choices[i].size() + 1];
			strcpy(cstr, _choices[i].c_str());  
			move(y, x);
			wprintw(win,"%d %s", i+1, cstr); //n'accepte qu un char *
			y += 2; 
		}

	}
	std::size_t size(){return _size;}
	std::string get_choice(ptrdiff_t idx){return _choices[idx];}
	bool verify_choice(int choice){return true ? choice > 0 && choice <= _size : false;}

	//application
	virtual void execute_choice(int choice)=0;

	//destructor
	virtual ~Menu(){delete[] _choices;}
};


class ConnexionMenu final: public Menu{
public:
	ConnexionMenu(): Menu({"Connexion", "Inscription"}){}
	void execute_choice(int choice) override{
		if(choice == 1){
			std::cout << "Vous avez choisie de vous connecter";
		}
		else if(choice == 2){std::cout << "Vous avez choisie de vous inscrire";}
	}

	virtual ~ConnexionMenu()=default;
	
};

class MainMenu final: public Menu{
public:
	MainMenu() : Menu({"Nouvelle partie", "Gestion des amis",\
		"Classement","Profile"}){}
	void execute_choice(int choice) override{
		switch(choice){
			case 1:
				std::cout << "Vous avez choisie de crée une partie";
				break;
			case 2:
				std::cout << "Vous avez choisie d'aller gérer vos amis";
				break;
			case 3:
				std::cout << "Vous avez choisie de voir le classement";
				break;
			case 4:
				std::cout << "Vous avez choisie de voir votre profile";
				break;
			default:
				break;
		}
	}
	virtual ~MainMenu()=default;
	
};


class FriendMenu final: public Menu{

public:
	FriendMenu(): Menu({"Ajouter un ami", "Supprimer un ami",\
		"Liste d'ami","Demandes d'ami"}){}

	void execute_choice(int choice) override{
		switch(choice){
			case 1:
				std::cout << "Vous avez choisie d'ajouter un ami";
				break;
			case 2:
				std::cout << "Vous avez choisie de supprimer un ami";
				break;
			case 3:
				std::cout << "Vous avez choisie de voir vos amis";
				break;
			case 4:
				std::cout << "Vous avez choisie de voir vos demandes d'amis";
				break;
			default:
				break;
		}
	}

	virtual ~FriendMenu()=default;


};





#endif //MENU_HPP