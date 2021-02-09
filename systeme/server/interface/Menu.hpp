/*
	Ajouter:
		titre aux menu
		option quitter pour venir au précédent menu
	Bugs:
		Entrez autre chose qu un nombre dans get_user_choice casse la machine!
*/

#ifndef Menu_HPP
#define Menu_HPP

#include <iostream>
#include <sys/types.h>

class Menu{
	size_t _size;
	std::string *_choices; 
	virtual void _dsp (std::ostream& out) const{
		for (size_t i = 0; i < _size; ++i){
			out<<"                                             "<<i+1<<" "<<_choices[i]<<"\n";}
	} 
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
	
	//getters & setters
	virtual void get_user_choice(){
		int choice; 
		std::cout<<"                                             "; // 13*" " abrege le 
		std::cout<< "Votre choix >>  ";
		std::cin>>choice;
		while(not verify_choice(choice)){
			system("clear");
			std::cout<<*this;
			std::cout<<"                                             "; // 13*" " abrege le 
			std::cout<< "Option non valide! \n";
			std::cout<<"                                             "; // 13*" " abrege le 
			std::cout<< "Entrez un choix valide >>  ";
			std::cin>>choice;
		}
		execute_choice(choice);
	}


	//utilities (maybe not necessary)
	std::size_t size(){return _size;}
	std::string get_choice(ptrdiff_t idx){return _choices[idx];}
	bool verify_choice(int choice){return true ? choice > 0 && choice <= static_cast<int>(_size): false;}

	//application (depend of choices!)
	virtual void execute_choice(int choice)=0;

	//destructor
	virtual ~Menu(){delete[] _choices;}

	//extern
	friend inline std::ostream& operator<< (std::ostream& out, const Menu& m){
		system("clear");
		out << "\n\n\n";
		m._dsp(out);
		out << "\n\n\n";
		return out;
	}

	//copie
	Menu(const Menu&)=default;
	Menu& operator=(const Menu&)=default;
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