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
}

int Menu::home(){ //a decouper en fonction
	int choice = window.print_menu(3, connexion_menu);
	char pseudo[20], pswd[20], error[64]; bool success = false; 
	bool quit = 0; int res; 
	switch(choice){
		case 1: //sign in
			while(not success){
				quit = window.get_connexion(pseudo, pswd, error);
				success = (verify_pseudo_format(pseudo)  and  verify_pswd_format(pswd)); //verify syntax
				if(quit){
					res = HOME; //return home
					success = true; //stop loop
				 }
				else if(success){
					success = _client->signIn(pseudo, pswd); //if user exist!
					if(not success){sprintf(error, "User doesn't exist!");}
				}
				else{sprintf(error, "Syntaxe error!");}
			}
			_client->set_pseudo(pseudo);
			res = MAIN; //connexion successed
			break; 
		case 2: //sign up
			while(not success){
				quit = window.get_connexion(pseudo, pswd, error);
				success = (verify_pseudo_format(pseudo)  and  verify_pswd_format(pswd)); //verify syntax
				if(quit){
					res = HOME; //return home
					success = true; //stop loop
				}
				else if(success){
					success = _client->signUp(pseudo, pswd); //if user exist!
					if(not success){sprintf(error, "Pseudo already taked!");}
				}
				else{sprintf(error, "Syntaxe error!");}
			}
			res = MAIN; //connexion successeed
			_client->set_pseudo(pseudo); //peut être laisser le client le faire dans sign up
			break;
		default: //quit programme
			res = -1;
			break;
	}
	return res; //next menu
}



int  Menu::friends(){ //decouper en fonction
	int choice = window.print_menu(5, friends_menu);
	char buffer[100]; char msg[164];
	std::vector<char*> vect; size_t size;
	int accepted=0; int res; char error[64];
	switch(choice){
		case 1: //Friend list
			_client->getFriendList(buffer);
			parse.pseudo_list_from_str(buffer, vect);
			window.print_friends(vect);
			res = FRIENDS; //return to friends menu 
			break;
		case 2: //Friend request
			_client->getFriendRequest(buffer);
			parse.pseudo_list_from_str(buffer, vect);
			size = vect.size();
			for (size_t i = 0; i < size; ++i){
				accepted = window.print_invitation(vect[i]);
				if(accepted ==1){
					_client->addFriend(vect[i]);
				} //le server doit supprimer les demande d'amis tout ceux ajouté ou refusé
				else if(not accepted){
					//prevenir le serveur;
				}
				else if(accepted == -1){ //quit
					break;
				}//quit 
				//else : pass next elem
			}
			res = FRIENDS; //return to friend menu
			break;
		case 3: //add friend
			while(not accepted){ //recycle variable accepted
				accepted = window.get_pseudo(buffer, error); 
				if(accepted){
					accepted = verify_pseudo_format(buffer);
					if(accepted){ //client enter a pseudo
						accepted = _client->addFriend(buffer);
						if(accepted==0){ //sent
							sprintf(msg, "Your invitation had been sent to %s ",buffer);
							accepted = 1;//stop loop
						}
						else if(accepted==1){ //already Friends
							sprintf(msg, "%s and you are already friends. check your friendlist", buffer);
						}
						else if(accepted==2){ //user doesn't exist
							sprintf(msg, "%s doesn't exist. Check your syntaxe", buffer);
							accepted = 0;//loop
						}
						window.print_alert(msg);
					}
				}
				else{ //quit
					accepted = 1; //stop loop
				}
			}
			res = FRIENDS;
			break;
		case 4: //remove friend
			while(not accepted){ //recycle variable accepted
				accepted = window.get_pseudo(buffer, error); 
				if(accepted){
					accepted = verify_pseudo_format(buffer);
					if(accepted){ //client enter a pseudo
						accepted = _client->delFriend(buffer);
						if(accepted==0){ //deleted
							sprintf(msg, "You and %s are no more friends.",buffer);
							accepted = 1;//stop loop
						}
						else if(accepted==1){ //already not friends
							sprintf(msg, "%s and you are notfriends.", buffer);
						}
						else if(accepted==2){ //user doesn't exist
							sprintf(msg, "%s doesn't exist. Check your syntaxe", buffer);
							accepted = 0;//loop
						}
						window.print_alert(msg);
					}
				}
				else{accepted = 1;} //stop loop ==> quit
			}
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
	std::vector<Profile*> prof;
	int choice = window.print_menu(5, friends_menu);
	Profile profile;
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
			parse.leaderboard_from_str(buffer, prof);
			window.print_leaderboard(prof);
			res = MAIN;
			break;
		case 4:  //profils
			_client->get_profile(buffer);
			parse.profile_from_str(buffer, &profile);
			window.print_profile(&profile);
			res = MAIN;
			break;
		default: //log out
			res = HOME;
			break;

	}

	return res;
}