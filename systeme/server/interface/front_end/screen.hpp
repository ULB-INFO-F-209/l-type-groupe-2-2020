#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include <iostream>

namespace Screen{

	//MENU TITLES
	extern std::string HOME_TITLE;
	extern std::string MAIN_TITLE;
	extern std::string FRIENDS_TITLE;
	extern std::string GAME_TITLE;

	//OTHER MENU TITLE
	extern std::string SIGN_IN;
	extern std::string SIGN_UP;
	extern std::string ADD_FRIEND;
	extern std::string DEL_FRIEND;
	extern std::string REQUEST;
	extern std::string YOUR_FRIENDS;
	extern std::string PROFILE;
	extern std::string LEADERBOARD;

	//SAYING FOR MENU 
	extern std::string HOME_SAYING;
	extern std::string MAIN_SAYING;
	extern std::string MAIN_SAYING2;
	extern std::string FRIENDS_SAYING;
	extern std::string FRIENDS_SAYING2;
	extern std::string GAME_SAYING;
	extern std::string SIGN_IN_SAYING;
	extern std::string SIGN_UP_SAYING;
	extern std::string SIGN_UP_SAYING2;
	extern std::string SIGN_UP_SAYING3;
	extern std::string ADD_SAYING;
	extern std::string ADD_SAYING2;
	extern std::string DEL_SAYING;
	extern std::string REQUEST_SAYING;
	extern std::string YFRIENDS_SAYING;
	extern std::string PROFILE_SAYING;
	extern std::string LEADBOARD_SAYING;

	//ERROR MESSAGES
	extern std::string SHORT_PSEUDO;
	extern std::string SHORT_PSWD;
	extern std::string SHORT_ALL;

	//CAPTION
	extern std::string PSEUDO_ZONE;
	extern std::string PSWD_ZONE;
	extern char CURSOR;
	extern char MASK;
	extern std::string PSEUDO;
	extern std::string SCORE;

	//choice 
	extern int HOME;
	extern int MAIN;
	extern int FRIENDS2;
	extern int GAME;
	extern int S_IN;
	extern int S_UP;
	extern int ADD;
	extern int DEL;
	extern int REQ;
	extern int Y_FRIENDS;
	extern int PROF;
	extern int LEADB;

}


#endif