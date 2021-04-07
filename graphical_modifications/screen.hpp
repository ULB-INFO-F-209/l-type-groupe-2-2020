#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include <iostream>

namespace Screen{

	//MenuTerminal TITLES
	extern std::string HOME_TITLE;
	extern std::string MAIN_TITLE;
	extern std::string FRIENDS_TITLE;
	extern std::string LOBBY_TITLE;

	//OTHER MenuTerminal TITLE
	extern std::string SIGN_IN;
	extern std::string SIGN_UP;
	extern std::string ADD_FRIEND;
	extern std::string DEL_FRIEND;
	extern std::string REQUEST;
	extern std::string YOUR_FRIENDS;
	extern std::string PROFILE;
	extern std::string LEADERBOARD;
	extern std::string  CHECK_USER;
	extern std::string  PROFILE2;

	//SAYING FOR MenuTerminal 
	extern std::string HOME_SAYING;
	extern std::string MAIN_SAYING;
	extern std::string MAIN_SAYING2;
	extern std::string Y_FRIENDS_SAYING;
	extern std::string Y_FRIENDS_SAYING2;
	extern std::string LOBBY_SAYING;
	extern std::string LOBBY_SAYING2;
	extern std::string SIGN_IN_SAYING;
	extern std::string SIGN_IN_SAYING2;
	extern std::string SIGN_UP_SAYING;
	extern std::string ADD_SAYING;
	extern std::string ADD_SAYING2;
	extern std::string DEL_SAYING;
	extern std::string DEL_SAYING2;
	extern std::string REQUEST_SAYING;
	extern std::string FRIENDS_SAYING;
	extern std::string PROFILE_SAYING;
	extern std::string PROFILE2_SAYING;
	extern std::string LEADBOARD_SAYING;
	extern std::string CHECK_USER_SAYING;
	extern std::string CHECK_USER_SAYING2;


	//ERROR MESSAGES
	extern std::string SHORT_PSEUDO;
	extern std::string SHORT_PSWD;
	extern std::string SHORT_ALL;
	extern std::string NO_USER_MSG;
	extern std::string TAKEN_PSEUDO_MSG;
	extern std::string ALREADY_FRIENDS;
	extern std::string NOT_FRIENDS;
	extern std::string ALREADY_REQUESTED;
	extern std::string YOURSEL_MSG;
	extern std::string DEFAULT_ERROR;

	//INSTRUCTION
	extern std::string SIGN_UP_SAYING1;
	extern std::string SIGN_UP_SAYING2;
	extern std::string BACK;
	extern std::string SWITCH;
	extern std::string RANGE;

	//CAPTION
	extern std::string PSEUDO_ZONE;
	extern std::string PSWD_ZONE;
	extern char CURSOR;
	extern char MASK;
	extern std::string PSEUDO;
	extern std::string SCORE;

	//SECTIONS
	const int HOME = 0;
	const int MAIN = 1;
	const int FRIENDS = 2;
	const int LOBBY  = 3;
	const int S_IN = 4;
	const int S_UP = 5;
	const int ADD = 6;
	const int DEL = 7;
	const int REQ = 8;
	const int Y_FRIENDS = 9;
	const int PROF = 10;
	const int LEADB = 11;

	//ERROR
	const int LEN_ERROR = 0, LEN_PSEUDO = 1, LEN_PSWD = 2;
	const int NO_USER_ERROR = 3, TAKEN_PSEUDO = 4, FRIENDS_ALREADY  = 5;
	const int FRIENDS_YET = 6, REQ_ALREADY =7;
	const int NO_ERROR = -1, YOURSELF_ERROR = 8;

	//CONSTANTES
	const int NB_MIN_CARA = 2;
	const int NB_MAX_CARA = 7;
}


#endif