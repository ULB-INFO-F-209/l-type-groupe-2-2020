#ifndef SCREEN_HPP
#define SCREEN_HPP

namespace Screen{

	//MENU TITLES
	char HOME_TITLE[] = "H O M E";
	char MAIN_TITLE[] = "M A I N  M E N U";
	char FRIENDS_TITLE[] = "F R I E N D S";
	char GAME_TITLE[] = "G A M E";

	//OTHER MENU TITLE
	char SIGN_IN[] = "S I G N  I N";
	char SIGN_UP[] = "S I G N  U P";
	char ADD_FRIEND[] = "A D D  F R I E N D";
	char DEL_FRIEND[] = "D E L  F R I E N D";
	char REQUEST[] = "Y O U R  F R I E N D 'S  R E Q U E S T S";
	char YOUR_FRIENDS[] ="Y O U R  F R I E N D S";
	char PROFILE[] = "Y O U R  P R O F I L E";
	char LEADERBOARD[] =" L E A D E R B O A R D";

	//SAYING FOR MENU 
	char HOME_SAYING[] = "May all who enter as guest leaves as regular user !";
	char MAIN_SAYING[] = "Whoever said money can't buy hapiness";
	char MAIN_SAYING2[] = "has clearly never ...trouve la suite";
	char FRIENDS_SAYING[] = "Friends are always with you whether";
	char FRIENDS_SAYING2[] = "they are imaginary or virtual !";
	char GAME_SAYING[] = "Win the game before is played !";
	char SIGN_IN_SAYING[] = "";
	char SIGN_UP_SAYING[] = "Your pseudo and password must be at least 7 characters long";
	char SIGN_UP_SAYING2[] = "and maximum 15. Only letters, numbers and the";
	char SIGN_UP_SAYING3[] = "underscore character are allowed.";
	char ADD_SAYING[] = "Making new friends shouldn't mean losing old ones.";
	char ADD_SAYING2[] = "But you can only have 100 friends there !";
	char DEL_SAYING[] = " ";
	char REQUEST_SAYING[] = " ";
	char YFRIENDS_SAYING[] = "";
	char PROFILE_SAYING[] = "BE PROUD OF YOUR SCORE!";
	char LEADBOARD_SAYING[] = "";

	//ERROR MESSAGES
	char SHORT_PSEUDO[] = "Pseudo is too short!";
	char SHORT_PSWD[] = "Password is too short!";
	char SHORT_ALL[] = "Pseudo and password are too short!";

	//CAPTION
	char PSEUDO_ZONE[] = "PSEUDO :";
	char PSWD_ZONE[] = "PASSWORD :";
	char CURSOR = '|';
	char MASK = '*';
	char PSEUDO[30] = "Pseudo : ";
	char SCORE[30] = "Score : ";

	//choice 
	int const HOME = 0;
	int const MAIN = 1;
	int const FRIENDS = 2;
	int const GAME = 3;
	int const S_IN = 4;
	int const S_UP = 5;
	int const ADD = 6;
	int const DEL = 7;
	int const REQ = 8;
	int const Y_FRIENDS = 9;
	int const PROF = 10;
	int const LEADB = 11;

}


#endif