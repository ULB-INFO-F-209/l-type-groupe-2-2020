#include "screen.hpp"
namespace Screen{

	//MenuTerminal TITLES
	std::string HOME_TITLE = "H O M E";
	std::string MAIN_TITLE = "M A I N  M E N U";
	std::string FRIENDS_TITLE = "F R I E N D S";
	std::string LOBBY_TITLE = "L O B B Y";

	//OTHER MenuTerminal TITLE
	std::string  SIGN_IN = "S I G N  I N";
	std::string  SIGN_UP = "S I G N  U P";
	std::string  ADD_FRIEND = "A D D  F R I E N D";
	std::string  DEL_FRIEND = "D E L  F R I E N D";
	std::string  REQUEST = "Y O U R  F R I E N D 'S  R E Q U E S T S";
	std::string  YOUR_FRIENDS ="Y O U R  F R I E N D S";
	std::string  PROFILE = "Y O U R  P R O F I L E";
	std::string  PROFILE2 = "P R O F I L E";
	std::string  LEADERBOARD =" L E A D E R B O A R D";
	std::string  CHECK_USER = "I D E N T I T Y  V E R I F I C A T I O N ";

	//SAYING FOR MenuTerminal 
	std::string HOME_SAYING = "May all who enter as guest leaves as regular user !";
	std::string MAIN_SAYING = "Whoever said money can't buy hapiness";
	std::string MAIN_SAYING2 = "has clearly already played this game";
	std::string Y_FRIENDS_SAYING = "A sweet friendship refreshes the soul, ";
	std::string Y_FRIENDS_SAYING2 = " unless you created them yourself !";
	std::string LOBBY_SAYING = "Winning is not everything, it's the only thing.";
	std::string LOBBY_SAYING2 = "So keep playing !";
	std::string SIGN_IN_SAYING = "Staying home saves lives.";
	std::string SIGN_IN_SAYING2 = "Playing this game will save yours.";
	std::string SIGN_UP_SAYING = "Welcome into your nightmare! Hope you will love it ! XOXO";
	std::string ADD_SAYING = "Making new friends shouldn't mean losing old ones.";
	std::string ADD_SAYING2 = "But you can only have 100 friends here !";
	std::string DEL_SAYING = "Fortunately, it's not as easy to unfriend";
	std::string DEL_SAYING2 = "someone in real life as your're doing now.";
	std::string REQUEST_SAYING = "Friends becomes our chosen family. So don't accept anyone !";
	std::string FRIENDS_SAYING = "If you want the rainbow, you have to endure the rain.";
	std::string PROFILE_SAYING = "Winners are losers who never quit. So try again to be the best !";
	std::string PROFILE2_SAYING = "Would you like to be friend with this user ?";
	std::string LEADBOARD_SAYING = "Win or learn ! Never lose. ";
	std::string CHECK_USER_SAYING = "We are who we are. Not who we say we are.";
	std::string CHECK_USER_SAYING2 = "So prove that there is a second player !";

	//INSTRUCTIONS
	std::string SIGN_UP_SAYING1 = "Username and password must be at least 7 characters long and maximum 15.";
	std::string SIGN_UP_SAYING2 = "Only letters, numbers and the underscore characters are allowed.";
	std::string BACK = "Don't you know how to return? Use the keyleft !";
	std::string SWITCH = "Use the keyup and keydown to navigate on a MenuTerminal !";
	std::string RANGE = "Use the keyup and keydown to change value !";



	//ERROR MESSAGES
	std::string SHORT_PSEUDO = "Username is too short!";
	std::string SHORT_PSWD = "Password is too short!";
	std::string SHORT_ALL = "Username and password are too short!";
	std::string NO_USER_MSG = "User does not exist!";
	std::string TAKEN_PSEUDO_MSG = "This Username is already taken. Try to sign in.";
	std::string ALREADY_FRIENDS = "You are already friends. check your friendlist";
	std::string NOT_FRIENDS =  "You are not friends yet";
	std::string ALREADY_REQUESTED =  "You had already sent a request!";
	std::string YOURSEL_MSG = "What is your username? And what did you enter?";
	std::string DEFAULT_ERROR = "There is an error. Try again !";
	//CAPTION
	std::string PSEUDO_ZONE = "USERNAME :";
	std::string PSWD_ZONE = "PASSWORD :";
	char MASK = '*';
	char CURSOR = '|';
	std::string Username = "USERNAME : ";
	std::string SCORE = "SCORE : ";
}
