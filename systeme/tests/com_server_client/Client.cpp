#include "Client.hpp"

/*
	Notes : 
		Sending and reading has to be in one function (repetions)
		TODO : éffacer les prints de debug (ZÉRO COUT !!)
		Le leaderboard doit être déja trié
*/

//constructor
Client::Client(){
	pid_t pid_process = getpid();
	_pid = pid_process;
	sprintf(_pipe_from_server,"%s%s%d", Constante::PIPE_PATH,Constante::BASE_PIPE_FILE, pid_process); //nom a lire
	sprintf(_pipe_to_server, "%s%s", Constante::PIPE_PATH, Constante::PIPE_DE_REPONSE); //pipe où écrire
	char test[100];
	sprintf(test,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_CONNEXION); //nom a lire

	//sending process pid : mandatory to do the first connexion;
	_fd_send_query= open(test, O_WRONLY); 
	char buffer[Constante::CHAR_SIZE]; 
	sprintf(buffer,"%d", pid_process);
	write(_fd_send_query, buffer, sizeof(buffer)); 
	close(_fd_send_query);
	std::cout << "nom pipe = " << _pipe_from_server << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}

//utilities
void Client::communication(char *buffer){
	_fd_send_query =  open(_pipe_to_server, O_WRONLY); 
	write(_fd_send_query, buffer, Constante::CHAR_SIZE); //sending query
	close(_fd_send_query);
	//char response[Constante::CHAR_SIZE];
	//sprintf(response, "%s%s%d", Constante::PIPE_PATH, Constante::BASE_PIPE_FILE, getpid());
	//mkfifo(response, Constante::PIPE_MODE);
	int ret = open(_pipe_from_server, O_RDONLY);
	/*
	while (ret != EEXIST)
	{
		std::cout << "nexiste pas" << std::endl;
		ret = open(_pipe_from_server, O_RDONLY);
	}
	*/
	std::cout << _pipe_from_server << std::endl;
	if (ret != -1)
	{
		char buff[Constante::CHAR_SIZE];
		std::cout << "je rentre"<<std::endl;
		while(true){
			int res = read(ret, buff, Constante::CHAR_SIZE);
			if (res == -1)
            {
                std::cout << "connexion echouée"<<std::endl;
            }
            else{
            	int aissa = atoi(buff);
            	std::cout << "connexion du processus :" << aissa <<std::endl;
            	break;
			}
		}
		std::cout << buffer << std::endl;
	}
	close(ret);
}

//Communication
bool Client::signIn(char *pseudo, char *pswd){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Ma&%s&%s&%d", pseudo, pswd, _pid);
	communication(buffer);
	bool success = atoi(buffer); // 0: User doesn't exist || 1: has been connected
	if(success){strcpy(_pseudo, pseudo);}
	
	return success; 
}

bool Client::signUp(char *pseudo, char *pswd){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mb&%s&%s&%d", pseudo, pswd, _pid);
	communication(buffer);
	bool success = atoi(buffer); // 0: pseudo already taked || 1:new account had been created
	if(success){strcpy(_pseudo, pseudo);}
	
	return success; 
}


bool Client::addFriend(char *p_friend){ //no need to check 
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mc&%s&%s&%d", _pseudo, p_friend,_pid);
	communication(buffer);
	bool state = atoi(buffer); // 0: No space || 1:Friend added

	return state; 
}

int Client::delFriend(char *p_friend){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Md&%s&%s&%d", _pseudo, p_friend,_pid);
	communication(buffer);
	int state = atoi(buffer); // 0 , 1, 2 = deleted, not friend yet, pseudo error

	return state; 
}

int Client::sendFriendRequest(char *p_friend){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Me&%s&%s&%d", _pseudo, p_friend,_pid);
	communication(buffer);
	bool state = atoi(buffer); // 0:request sent || 1:already in request ||2: Already Friend||3:error pseudo

	return state; 
}

void  Client::getFriendRequest(char *res){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mf&%s&%d", _pseudo, _pid);
	communication(buffer);
	strcpy(res, buffer); //retour res
}

void Client::delFriendRequest(char *pseudo){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mf&%s&%d", _pseudo, _pid);
	communication(buffer);
}

void Client::getFriendList(char *res){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mg&%s&%d", _pseudo, _pid);
	communication(buffer);
	strcpy(res, buffer); //pseudo1|score&pseudo2|score&pseudo3|score...
}

void Client::checkLeaderboard(char * res){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mh&%d",_pid);
	communication(buffer); 
	strcpy(res, buffer); //pseudo1|score&pseudo2|score&pseudo|score....
}

void Client::get_profile(char *res){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mi&%d",_pid);
	communication(buffer); 
	strcpy(res, buffer); //pseudo1&score
}

void Client::exit(){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mj&%d",_pid);
	communication(buffer); //server return exit code 0
	//the server should delete all pipe we used!
	//and destruct my game if I was playing
}

//game
bool Client::checkID(char *pseudo, char*pswd){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Pf&%s&%s&%d", pseudo, pswd, _pid);
	communication(buffer);
	bool success = atoi(buffer); // "0" ou "1" => User doesn't exist || User exist

	return success;
}

int  Client::createGame(char *game_info){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Pp&%s&%d", game_info,_pid);
	communication(buffer);
	int ID_game = atoi(buffer); //-1 if error
	if(ID_game != -1){
		_currentGameID = ID_game; 
		_inGame = true;
	}
	return ID_game;
}

//destructor
Client::~Client(){
	//exit(); //kill process
}
