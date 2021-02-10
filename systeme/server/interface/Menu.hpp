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
#include "Client.hpp"

class Menu{
	size_t _size;
	std::string *_choices; 
	virtual void _dsp (std::ostream& out) const{
		for (size_t i = 0; i < _size; ++i){
			out<<"                                             "<<i+1<<" "<<_choices[i]<<"\n";}
	} 
protected: 
	Client * _client;//execute some queries
public:
	//constructeur
	explicit Menu(const std::initializer_list<std::string>& init, Client*cl)noexcept : 
	_size(init.size()), _choices(new std::string[_size]){
		const std::string* p = init.begin();
		ptrdiff_t max = static_cast<ptrdiff_t>(_size);
		for (ptrdiff_t i = 0; i < max; ++i){
			_choices[i] = p[i];	
		}
		_client = cl;
	}
	
	//getters & setters
	virtual int  get_user_choice(){
		int choice; 
		std::cout<<"                                             "; // 13*" " abrege le 
		std::cout<< "Votre choix >>  ";
		std::cin>>choice;
		while(choice <= 0 && choice > static_cast<int>(_size)){
			system("clear");
			std::cout<<*this;
			std::cout<<"                                             "; // 13*" " abrege le 
			std::cout<< "Option non valide! \n";
			std::cout<<"                                             "; // 13*" " abrege le 
			std::cout<< "Entrez un choix valide >>  ";
			std::cin>>choice;
		}
		return choice;
	}

	//application (depend of choices!)
	virtual int execute_choice(int choice)=0; //return status
	virtual int start_menu(){
		int res = 0;
		std::cout<<*this;
		res = execute_choice(get_user_choice());
		return res;
	}

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
	ConnexionMenu(Client *client): Menu({"Sign in", "Sign up", "quit"}, client){}
	int execute_choice(int choice) override{
		//choice is already verified 
		int res = 0; //retour

		switch(choice){
			char pseudo[20], pswd[20];
			case 1: //sign in
				system("clear");
				std::cout<< "Pseudo : ";
				std::cin>> pseudo;
				std::cout<< "Password: ";
				std::cin>> pswd;

				while(not _client->signIn(pseudo, pswd)){ //mettre option de retour
					system("clear");
					std::cout <<" You have an error in your pseudo or password\n\n";
					std::cout<< "Pseudo : ";
					std::cin>> pseudo;
					std::cout<< "Password: ";
					std::cin>> pswd;
				}
				system("clear");
				std::cout<<"\n\nWelcome\n\n"; //faire une belle transition
				res = 1; //ouvrir le Menu
				break;
			case 2: //sign up
				//fair un beau message d'accueil;
				system("clear");
				std::cout <<"Your pseudo and passsword must be minimum size 8 and not exceed 20 characters\n";
				std::cout <<"Your pseudo can only contain letters, numbers and underscore!\n";
				std::cout <<"Your password can't have the & caracter\n\n";
				std::cout<< "Pseudo : ";
				std::cin>> pseudo;
				std::cout<< "Password: ";
				std::cin>> pswd;
				while(not _client->signUp(pseudo, pswd)){
					system("clear");
					std::cout <<"Your pseudo and passsword must be minimum size 8 and not exceed 20 characters\n";
					std::cout <<"Your pseudo can only contain letters, numbers and underscore!\n";
					std::cout <<"Your password can't have the & caracter\n\n";
					std::cin>> pseudo;
					std::cout<< "Password: ";
					std::cin>> pswd;
				}
				break;
			default: //quit
				break;
		}
		return res;
	}
	virtual ~ConnexionMenu()=default;
	
};

class MainMenu final: public Menu{
public:
	MainMenu(Client *client) : Menu({"New game", "Friends",\
		"Leaderboard","Profile", "Log out"},client){}
	int  execute_choice(int choice) override{
		/* return : 1 >> aller dans le friend menu
					0 >> log out
		*/
		int res = 0;
		switch(choice){
			case 1: //newgame à faire en dernier
				std::cout << "Vous avez choisie de crée une partie";
				std::cout << "cette partie n'est pas faite";
				break;
			case 2: //friend menu
				res = 1;
				break;
			case 3: //leaderboard
				std::cout << "Vous avez choisie de voir le classement";
				char board[256]; //augmenter un tableau c'est long
				_client->checkLeaderboard(board);
				system("clear");
				std::cout<<board;
				std::cout << "press q to quit"; //gere avec ncurses!
				break;
			case 4: //profile
				char profile[256];
				_client.

				break;
			default: //log out 
				break;
		}
		return res;
	}
	virtual ~MainMenu()=default;
	
};


class FriendMenu final: public Menu{

public:
	FriendMenu(Client *client): Menu({"Add friend", "Remove friend",\
		"Friend's list","Friend's request","quit"},client){}

	int execute_choice(int choice) override{
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