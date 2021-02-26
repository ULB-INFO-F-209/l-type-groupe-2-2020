#include "Menu.hpp"

void Menu::start_session(){
	int menu = HOME;
	while(menu != -1){ //-1 = quiter programme
		if(menu==HOME){
			menu = home();
		}
		else if(menu==MAIN){
			menu = main_m();
		}
		else if(menu==FRIENDS){
			menu = friends();
		}
	}
	//_client.exit();
	std::cout << "EXIT !"<<std::endl;
}

//MENU
int Menu::home(){
	int res=-1; 
	int choice = window.print_menu(SIZE_HOME, connexion_menu,HOME);
	switch(choice){
		case 0: //sign in
			res = connexion(true);
			break; 
		case 1: //sign up
			res = connexion(false);
			break;
		default: //quit programme
			res = -1;
			break;
	}
	return res; //next menu
}

int  Menu::friends(){ //decouper en fonction
	int res;
	int choice = window.print_menu(SIZE_FRIENDS_MENU, friends_menu, FRIENDS);
	switch(choice){
		case 0: //Friend list
			afficher_friends();
			res = FRIENDS; //return to friends menu 
			break;
		case 1: //Friend request
			request_management();
			res = FRIENDS; //return to friend menu
			break;
		case 2: //add friend
			add_del_friends(true);
			res = FRIENDS;
			break;
		case 3: //remove friend
			add_del_friends(false);
			res = FRIENDS;
			break;
		default: //back to main menu (-1)
			res = MAIN;
			break;
	}
	return res;

}

int  Menu::main_m(){
	int res; char buffer[100];
	std::vector<Profile> profile_list;
	Profile profile;
	int choice = window.print_menu(SIZE_MAIN_MENU, main_menu, MAIN);
	switch(choice){
		case 0: //new game
			//later
			res = MAIN; //crée jeu 
			break;
		case 1: //Friends
			res = FRIENDS;
			break; 
		case 2: //leaderboard
			_client.checkLeaderboard(buffer);
			profile_list_from_str(buffer, &profile_list);
			window.print_profile(&profile_list, LEADB);
			res = MAIN;
			break;
		case 3:  //profils
			_client.get_profile(buffer);
			profile_from_str(buffer, &profile);
			window.print_profile(&profile, PROF);
			res = MAIN;
			break;
		case 4:
			res = HOME; //log out
			break;
		default: //aucun touch accepter
			res = MAIN;
			break;
	}

	return res;
}

//home utilities
int Menu::connexion(bool sign_in){
	bool success = false, quit=false;
	char pseudo[20], pswd[20];
	int res = MAIN, error=NO_ERROR; //connexion successed
	int type = S_UP;

	if(sign_in)
		type = S_IN;

	while(not success and not quit){
		quit = window.get_connexion(pseudo, pswd, error,type);
		if(not quit){
			if(sign_in){
				success = _client.signIn(pseudo, pswd); //if user exist!
				if(not success){error = NO_USER;}
				else{error = NO_ERROR;}
			}
			else{
				success = _client.signUp(pseudo, pswd); //if user exist!
				if(not success){error = TAKEN_PSEUDO;}
				else{error = NO_ERROR;}
			}
			}
		else{
			res = HOME;
		}//return home
	}
	return res;
}

//Friends utilities
void Menu::afficher_friends(){
	char buffer[100];
	std::vector<Profile> vect;
	_client.getFriendList(buffer);
	profile_list_from_str(buffer, &vect); //parsing

	window.print_profile(&vect, Y_FRIENDS);
}

void Menu::request_management(){
	int ret=true; char buffer[100]; 
	int answer[2] = {0,0};
	while(ret){
		_client.getFriendRequest(buffer);
		std::vector<Profile> vect;
		profile_list_from_str(buffer, &vect);;
		ret = window.print_profile(&vect, REQ, answer); 
		int idx = answer[0];
		int accepted = answer[1];
		if(accepted and ret)
			_client.addFriend(vect[idx].pseudo);
		else if (ret)
			_client.delFriendRequest(vect[idx].pseudo);	
		sleep(3);
	}
}

void Menu::add_del_friends(bool add){
	char  buffer[20];
	int success=1, error = NO_ERROR; 
	bool quit = false;
	while(success and not quit){ 
		if(add){
			quit = window.get_pseudo(buffer,error,ADD); 
			if(not quit){
				success = _client.sendFriendRequest(buffer);
				if(success==1)
					error = REQ_ALREADY;
				else if (success==2)
					error = FRIENDS_ALREADY;
				else if(success==3)
					error = NO_USER;
				else
					error = NO_ERROR;
			}
		}
		else{
			quit = window.get_pseudo(buffer,error,DEL);
			if(not quit){
				success = _client.delFriend(buffer);
				if(success==1)
					error = FRIENDS_YET;
				else if (success==2)
					error = NO_USER;
				else
					error = NO_ERROR;
			}
		}
	}
}

