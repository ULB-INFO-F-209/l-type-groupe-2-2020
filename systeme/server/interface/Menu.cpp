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
	_client->exit();
}

//MENU
int Menu::home(){
	int res; 
	int choice = window.print_menu(SIZE_HOME, connexion_menu);
	switch(choice){
		case 1: //sign in
			res = connexion(true);
			break; 
		case 2: //sign up
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
	int choice = window.print_menu(SIZE_FRIENDS_MENU, friends_menu);
	switch(choice){
		case 1: //Friend list
			afficher_friends();
			res = FRIENDS; //return to friends menu 
			break;
		case 2: //Friend request
			request_management();
			res = FRIENDS; //return to friend menu
			break;
		case 3: //add friend
			add_del_friends(true);
			res = FRIENDS;
			break;
		case 4: //remove friend
			add_del_friends(false);
			res = FRIENDS;
			break;
		default: //back to main menu
			res = MAIN;
			break;
	}
	return res;

}

int  Menu::main_m(){
	int res; char buffer[100];
	std::vector<Profile*> profile_list;
	Profile profile;
	int choice = window.print_menu(SIZE_FRIENDS_MENU, friends_menu);
	switch(choice){
		case 1: //new game
			//later
			res = MAIN;
			break;
		case 2: //Friends
			res = FRIENDS;
			break; 
		case 3: //leaderboard
			_client->checkLeaderboard(buffer);
			profile_list_from_str(buffer, profile_list);
			window.print_profile(profile_list);
			res = MAIN;
			break;
		case 4:  //profils
			_client->get_profile(buffer);
			profile_from_str(buffer, &profile);
			window.print_profile(&profile);
			res = MAIN;
			break;
		default: //log out
			res = HOME;
			break;

	}

	return res;
}

//home utilities
int Menu::connexion(bool sign_in){
	bool success = false, quit = false; 
	char pseudo[20], pswd[20];
	int res = MAIN, error=NO_ERROR; //connexion successed
	while(not success and not quit){
		if(S_IN)

			quit = window.get_connexion(pseudo, pswd, error,S_IN);
		if(not quit){
			res = HOME; //return home
		}
		else if(sign_in){ //sign in
			success = _client->signIn(pseudo, pswd); //if user exist!
			if(not success){error = NO_USER;}
		}
		else if(not sign_in){ //sign up
			success = _client->signUp(pseudo, pswd); //if user exist!
			if(not success){error = TAKEN_PSEUDO;}
		}
	}		

	return res;
}

//Friends utilities
void Menu::afficher_friends(){
	char buffer[100];
	std::vector<Profile*> vect;
	_client->getFriendList(buffer);
	profile_list_from_str(buffer, vect); //parsing
	window.print_profile(vect);
}

void Menu::request_management(){
	int accepted; char buffer[100]; 
	size_t i = 0;
	std::vector<Profile*> vect;
	_client->getFriendRequest(buffer);
	profile_list_from_str(buffer, vect);
	size_t size = vect.size();
	while(i < size and accepted != -1){
		accepted = window.print_invitation(vect[i]); // -1 = quit
		if(accepted ==1){
			_client->addFriend(vect[i]->pseudo);
		} 
		else if(not accepted){
			_client->delFriendRequest(vect[i]->pseudo);
		}
	}
}

void Menu::add_del_friends(bool add){
	char msg[164], buffer[100]; int success=0;
	while(not success){ 
		success = window.get_pseudo(buffer, msg); 
		if(success){
			success = verify_pseudo_format(buffer);
			if(success and add){ //client enter a pseudo
				success = _client->sendFriendRequest(buffer);
				get_msg(buffer, msg, success,true);
			}
			else if(success and not add){
				success = _client->delFriend(buffer);
				get_msg(buffer, msg, success,false);
			}
			window.print_alert(msg);
		}
		else{ //quit
			break;
		}
	}
}

void Menu::get_msg(char * pseudo, char *res, int msg, bool invitation){
	if(invitation){
		if(msg==0){ //sent
			sprintf(res, "Your invitation had been sent to %s ",pseudo);
		}
		else if(msg==1){ //already Friends
			sprintf(res, "%s and you are already friends. check your friendlist", pseudo);
		}
		else if(msg==2){ //user doesn't exist
			sprintf(res, "%s doesn't exist. Check your syntaxe", pseudo);
		}
	}
	else{ //remove friends
		if(msg==0){ //sent
			sprintf(res,  "You and %s are no more friends.",pseudo);
		}
		else if(msg==1){ //already Friends
			sprintf(res, "%s and you are not friends.", pseudo);
		}
		else if(msg==2){ //user doesn't exist
			sprintf(res, "%s doesn't exist. Check your syntaxe", pseudo);
		}
	}
}