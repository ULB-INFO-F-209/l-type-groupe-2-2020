#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include <iostream>

namespace Screen{

	//MENU TITLES
	const std::string HOME_TITLE = "H O M E";
	const std::string MAIN_TITLE = "M A I N  M E N U";
	const std::string FRIENDS_TITLE = "F R I E N D S";
	const std::string LOBBY_TITLE = "L O B B Y";

	//OTHER MENU TITLE
	const std::string  SIGN_IN = "S I G N  I N";
	const std::string  SIGN_UP = "S I G N  U P";
	const std::string  ADD_FRIEND = "A D D  F R I E N D";
	const std::string  DEL_FRIEND = "D E L  F R I E N D";
	const std::string  REQUEST = "Y O U R  F R I E N D 'S  R E Q U E S T S";
	const std::string  YOUR_FRIENDS ="Y O U R  F R I E N D S";
	const std::string  PROFILE = "Y O U R  P R O F I L E";
	const std::string  PROFILE2 = "P R O F I L E";
	const std::string  LEADERBOARD =" L E A D E R B O A R D";
	const std::string  CHECK_USER = "I D E N T I T Y  V E R I F I C A T I O N ";

	//SAYING FOR MENU 
	const std::string HOME_SAYING = "May all who enter as guest leaves as regular user !";
	const std::string MAIN_SAYING = "Whoever said money can't buy hapiness";
	const std::string MAIN_SAYING2 = "has clearly already played this game";
	const std::string Y_FRIENDS_SAYING = "A sweet friendship refreshes the soul, ";
	const std::string Y_FRIENDS_SAYING2 = " unless you created them yourself !";
	const std::string LOBBY_SAYING = "Winning is not everything, it's the only thing.";
	const std::string LOBBY_SAYING2 = "So keep playing !";
	const std::string SIGN_IN_SAYING = "Staying home saves lives.";
	const std::string SIGN_IN_SAYING2 = "Playing this game will save yours.";
	const std::string SIGN_UP_SAYING = "Welcome into your nightmare! Hope you will love it ! XOXO";
	const std::string ADD_SAYING = "Making new friends shouldn't mean losing old ones.";
	const std::string ADD_SAYING2 = "But you can only have 100 friends here !";
	const std::string DEL_SAYING = "Fortunately, it's not as easy to unfriend";
	const std::string DEL_SAYING2 = "someone in real life as your're doing now.";
	const std::string REQUEST_SAYING = "Friends becomes our chosen family. So don't accept anyone !";
	const std::string FRIENDS_SAYING = "If you want the rainbow, you have to endure the rain.";
	const std::string PROFILE_SAYING = "Winners are losers who never quit. So try again to be the best !";
	const std::string PROFILE2_SAYING = "Would you like to be friend with this user ?";
	const std::string LEADBOARD_SAYING = "Win or learn ! Never lose. ";
	const std::string CHECK_USER_SAYING = "We are who we are. Not who we say we are.";
	const std::string CHECK_USER_SAYING2 = "So prove that there is a second player !";

	//INSTRUCTIONS
	const std::string SIGN_UP_SAYING1 = "Username and password must be at least 7 characters long and maximum 15.";
	const std::string SIGN_UP_SAYING2 = "Only letters, numbers and the underscore characters are allowed.";
	const std::string BACK = "Don't you know how to return? Use the keyleft !";
	const std::string SWITCH = "Use the keyup and keydown to navigate on a menu !";
	const std::string RANGE = "Use the keyup and keydown to change value !";



	//ERROR MESSAGES
	const std::string SHORT_PSEUDO = "Username is too short!";
	const std::string SHORT_PSWD = "Password is too short!";
	const std::string SHORT_ALL = "Username and password are too short!";
	const std::string NO_USER_MSG = "User does not exist!";
	const std::string TAKEN_PSEUDO_MSG = "This Username is already taken. Try to sign in.";
	const std::string ALREADY_FRIENDS = "You are already friends. check your friendlist";
	const std::string NOT_FRIENDS =  "You are not friends yet";
	const std::string ALREADY_REQUESTED =  "You had already sent a request!";
	const std::string YOURSEL_MSG = "What is your username? And what did you enter?";
	const std::string DEFAULT_ERROR = "There is an error. Try again !";
	//CAPTION
	const std::string PSEUDO_ZONE = "USERNAME :";
	const std::string PSWD_ZONE = "PASSWORD :";
	const char MASK = '*';
	const char CURSOR = '|';
	const std::string Username = "USERNAME : ";
	const std::string SCORE = "SCORE : ";

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

/*void accept_friend(){
    const char* pseudo = (pseudo_line->text()).toUtf8().constData(); 
    std::cout << "pseudo   : "<< pseudo<<std::endl;
    _client.addFriend(pseudo);
}*/