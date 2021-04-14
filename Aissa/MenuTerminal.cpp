#include "MenuTerminal.hpp"

Interface MenuTerminal::window = Interface();

void MenuTerminal::start_session(){
	signal(SIGINT,handle_SIGINT);
	int menu = HOME;
	while(menu != -1){ //-1 = quiter programme
		if(menu==HOME)
			menu = home();
		else if(menu==MAIN)
			menu = main_m();
		else if(menu==FRIENDS)
			menu = friends();
		else if(menu==SETTINGS)
			menu = lobby();
	}
	//_client.exit();
	std::cout << "EXIT !"<<std::endl;
}

//MENU
int MenuTerminal::home(){
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

int  MenuTerminal::friends(){ //decouper en fonction
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

int  MenuTerminal::main_m(){
	int res; char buffer[Constante::CHAR_SIZE];
	std::vector<Profile> profile_list;
	Profile profile;
	int choice = window.print_menu(SIZE_MAIN_MENU, main_menu, MAIN);
	switch(choice){
		case 0: //new game
			//later
			res = SETTINGS; //crée jeu 
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

int MenuTerminal::lobby(){
	int res = SETTINGS; //return to lobby 
	Game_settings setting{}; int ret; bool stop = false;
	char buffer[Constante::CHAR_SIZE];
	std::string yes_no[] = {"Yes", "No"};
	std::string difficulty[] = {"easy", "medium", "hard"};
	_client.get_pseudo(setting.pseudo_hote);
	while(not stop){
		int choice = window.print_menu(SIZE_SETTINGS, settings_menu, LOBBY, &setting);
		switch(choice){
			case 0: //nb_of player
				get_players(&setting);
				break;
			case 1: //DROP_RATE
				setting.drop_rate = window.range(100, &setting, true);
				break; 
			case 2: //Ally_SHOT
				if (setting.nb_player == 2){
					ret = window.print_menu(2, yes_no, LOBBY,&setting);
					if(ret != -1)
						setting.ally_shot = (ret+1)%2;
				}

				break;
			case 3:  //live's number
				setting.nb_lives = window.range(3,&setting);
				break;
			case 4:	//difficulty
				ret = window.print_menu(3, difficulty, LOBBY, &setting);
				if(ret != -1){
					strcpy(setting.difficulty_str, difficulty[ret].c_str());
					setting.diff = !strcmp(setting.difficulty_str,"easy")? easy: !strcmp(setting.difficulty_str,"medium")? medium :hard;
				}
				break;
			case 5: 	//play
				create_game_to_str(buffer,&setting);
				_client.createGame(buffer);
				launch_game(&setting);
				break;
			default: // - 1 ==> quit 
				res = MAIN;
				stop = true;
				break;
		}
	}
	return res; 
}

//home utilities
int MenuTerminal::connexion(bool sign_in){
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
				if(not success){error = NO_USER_ERROR;}
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
void MenuTerminal::afficher_friends(){
	char buffer[Constante::CHAR_SIZE];
	std::vector<Profile> vect;
	_client.getFriendList(buffer);
	profile_list_from_str(buffer, &vect); //parsing

	window.print_profile(&vect, Y_FRIENDS);
}

void MenuTerminal::request_management(){
	int ret=true; char buffer[Constante::CHAR_SIZE]; 
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
	}
}

void MenuTerminal::add_del_friends(bool add){
	char  buffer[Constante::CHAR_SIZE];
	int success=1, error = NO_ERROR; 
	bool quit = false;
	while(success and not quit){ 
		if(add){
			quit = window.get_pseudo(buffer,error,ADD); 
			if(not quit){
				success = _client.sendFriendRequest(buffer);
				if(success==1){
					error = REQ_ALREADY;
				}
				else if (success==2)
					error = FRIENDS_ALREADY;
				else if(success==3)
					error = NO_USER_ERROR;
				else if(success==4){
					error = YOURSELF_ERROR;
				}
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
					error = NO_USER_ERROR;
				else if(success==3)
					error = YOURSELF_ERROR;
				else
					error = NO_ERROR;
			}
		}
	}
}

//game utilities
void MenuTerminal::get_players(Game_settings*set){

	int choice = 1; int error = NO_ERROR;
	bool quit=false; char pswd[20], pseudo[20];
	std::string options[3] = {"1", "2", "quit"}; bool success = false;

	choice = window.print_menu(3, options, LOBBY, set);

	if(choice==1){
		while(not success and not quit){
			quit = window.get_connexion(set->pseudo_other, pswd, error,LOBBY);
			_client.get_pseudo(pseudo);
			if(not quit and strcmp(set->pseudo_other,pseudo) != 0){

				success = _client.signIn(set->pseudo_other, pswd,false); //if user exist!
				if(not success){
					error = NO_USER_ERROR;
					set->nb_player = 1;
				}
				else{
					error = NO_ERROR;
					set->nb_player = 2;
				}
			}
			else if(!quit){
				error = YOURSELF_ERROR;
			}
		}
	}
	else if(choice==0)
		set->nb_player = 1;
}

void MenuTerminal::launch_game(Game_settings* game_option){
	DisplayGame display_game;
	display_game.init();
    bool gameOn = true;
    int inp = -1;
	std::string string_game_to_display;

    while(gameOn){

        inp = display_game.getInput();
		
		_client.send_game_input(inp);
		string_game_to_display = _client.read_game_pipe();
		if (string_game_to_display == Constante::GAME_END) break;
		display_game.parse_instruction(string_game_to_display);
		

    }
	string_game_to_display = _client.read_game_pipe();
	std::cout << string_game_to_display;
	display_game.drawEndGame(string_game_to_display);
    display_game.close();
}


void MenuTerminal::handle_SIGINT(int sig){
	char pipe_to_server[Constante::SIZE_pipe];
	sprintf(pipe_to_server, "%s%s", Constante::PIPE_PATH, Constante::PIPE_DE_REPONSE); //pipe où écrire
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mj&%d",getpid());
	int fd =  open(pipe_to_server, O_WRONLY); 
	write(fd, buffer, Constante::CHAR_SIZE);
	close(fd);
	std::cout << "Bye Bye"<< std::endl;
	window.erase_win();
	exit(EXIT_SUCCESS);
}