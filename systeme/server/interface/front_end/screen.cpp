#include "screen.hpp"
namespace Screen{

	//MENU TITLES
	std::string HOME_TITLE = "H O M E";
	std::string MAIN_TITLE = "M A I N  M E N U";
	std::string FRIENDS_TITLE = "F R I E N D S";
	std::string GAME_TITLE = "G A M E";

	//OTHER MENU TITLE
	std::string  SIGN_IN = "S I G N  I N";
	std::string  SIGN_UP = "S I G N  U P";
	std::string  ADD_FRIEND = "A D D  F R I E N D";
	std::string  DEL_FRIEND = "D E L  F R I E N D";
	std::string  REQUEST = "Y O U R  F R I E N D 'S  R E Q U E S T S";
	std::string  YOUR_FRIENDS ="Y O U R  F R I E N D S";
	std::string  PROFILE = "Y O U R  P R O F I L E";
	std::string  LEADERBOARD =" L E A D E R B O A R D";

	//SAYING FOR MENU 
	std::string HOME_SAYING = "May all who enter as guest leaves as regular user !";
	std::string MAIN_SAYING = "Whoever said money can't buy hapiness";
	std::string MAIN_SAYING2 = "has clearly never ...trouve la suite";
	std::string FRIENDS_SAYING = "Friends are always with you whether";
	std::string FRIENDS_SAYING2 = "they are imaginary or virtual !";
	std::string GAME_SAYING = "Win the game before is played !";
	std::string SIGN_IN_SAYING = "";
	std::string SIGN_UP_SAYING = "Your pseudo and password must be at least 7 acters long";
	std::string SIGN_UP_SAYING2 = "and maximum 15. Only letters, numbers and the";
	std::string SIGN_UP_SAYING3 = "underscore acter are allowed.";
	std::string ADD_SAYING = "Making new friends shouldn't mean losing old ones.";
	std::string ADD_SAYING2 = "But you can only have 100 friends there !";
	std::string DEL_SAYING = " ";
	std::string REQUEST_SAYING = " ";
	std::string YFRIENDS_SAYING = "";
	std::string PROFILE_SAYING = "BE PROUD OF YOUR SCORE!";
	std::string LEADBOARD_SAYING = "";

	//ERROR MESSAGES
	std::string SHORT_PSEUDO = "Pseudo is too short!";
	std::string SHORT_PSWD = "Password is too short!";
	std::string SHORT_ALL = "Pseudo and password are too short!";

	//CAPTION
	std::string PSEUDO_ZONE = "PSEUDO :";
	std::string PSWD_ZONE = "PASSWORD :";
	char CURSOR = '|';
	char MASK = '*';
	std::string PSEUDO = "Pseudo : ";
	std::string SCORE = "Score : ";

	//choice 
	int HOME = 0;
	int MAIN = 1;
	int FRIENDS = 2;
	int GAME = 3;
	int S_IN = 4;
	int S_UP = 5;
	int ADD = 6;
	int DEL = 7;
	int REQ = 8;
	int Y_FRIENDS = 9;
	int PROF = 10;
	int LEADB = 11;

}
