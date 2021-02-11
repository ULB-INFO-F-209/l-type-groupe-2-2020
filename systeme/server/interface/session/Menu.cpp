#include "Menu.hpp"

void Menu::start_session(){
	while(ret != -1){
		if(ret==HOME){
			std::thread home_menu(&Menu::home,this);
			home_menu.join(); //il v amettre a jour ret
		}
		else if(ret==MAIN){
			std::thread main_menu(&Menu::main_m,this);
		}
		else if(ret==FRIENDS){
			std::thread friends_menu(&Menu::friends,this);
		}
		else if(ret==-1){ //quitter le programme

		}
	}
}

void Menu::home(){
	int choice = window.print_menu(3, connexion_menu);
	char pseudo[20], pswd[20], error[64]; bool success = false; 
	bool quit = 0;
	switch(choice){
		case 1: //sign in
			while(not success){
				quit = window.get_connexion(pseudo, pswd, error);
				success = verify_format(pseudo, pswd); //verify syntax
				if(quit){
					set_ret(HOME);
				 	return;
				 }
				else if(success){
					success = _client->signIn(pseudo, pswd); //if user exist!
					if(not success){sprintf(error, "User doesn't exist!");}
				}
				else{sprintf(error, "Syntaxe error!");}
			}
			set_ret(MAIN); //connexion succeed
			_client->set_pseudo(pseudo);
			break; 
		case 2: //sign up
			while(not success){
				quit = window.get_connexion(pseudo, pswd, error);
				success = verify_format(pseudo, pswd); //verify syntax
				if(quit){
					set_ret(HOME);
					return;
				}
				else if(success){
					success = _client->signUp(pseudo, pswd); //if user exist!
					if(not success){sprintf(error, "Pseudo already taked!");}
				}
				else{sprintf(error, "Syntaxe error!");}
			}
			set_ret(MAIN); //connexion succeed
			_client->set_pseudo(pseudo);
			break;
		default: //quit programme
			set_ret(-1); 
			break;
	}
}



void Menu::friends(){
	int choice = window.print_menu(5, friends_menu);
	char buffer[256]; //peut_ëtre pas assé
	std::vector<char*> vect; size_t size;
	bool accepted; int res=0; char error[64];
	switch(choice){
		case 1: //Friend list
			_client->getFriendList(buffer);
			parse.pseudo_list_from_str(buffer, vect);
			window.print_friends(vect);
			set_ret(FRIENDS); //return to menu
			break;
		case 2: //Friend request
			_client->getFriendList(buffer);
			parse.pseudo_list_from_str(buffer, vect);
			size = vect.size();
			for (size_t i = 0; i < size; ++i){
				accepted = window.print_invitation(vect[i]);
				if(accepted){
					_client->addFriend(vect[i]);
				} //le server doit supprimer des demande d'amis tout ceux ajouté ou refusé
			}
			set_ret(FRIENDS);
			break;
		case 3: //add friend
			while(not res){
				res = window.get_pseudo(buffer, error); 
				if(res){
					res = verify_format(buffer, NULL);
					if(res){
						res = _client->addFriend(buffer);
						if(res==0){}
						else if(res==1)
						
					}
				}
				else{ //quit
					set_ret(FRIENDS);
					return;
				}
			break;
		case 4: //remove friend
			break;
		default: //back to main menu
			break;
	}

}

void Menu::main_m(){
	
}