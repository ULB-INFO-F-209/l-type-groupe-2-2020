#include "Client.hpp"


//constructor  
Client::Client():_pid(getpid()){

	//pipe's name
	sprintf(_pipe_from_server,"%s%s%d", Constante::PIPE_PATH,Constante::BASE_PIPE_FILE, _pid); 
	sprintf(_pipe_to_server, "%s%s", Constante::PIPE_PATH, Constante::PIPE_DE_REPONSE); 
	sprintf(_pipe_input_game, "%s%s%d", Constante::PIPE_PATH, Constante::BASE_INPUT_PIPE,_pid); 
	sprintf(_pipe_game_sett, "%s%s%d", Constante::PIPE_PATH, Constante::BASE_GAME_PIPE,_pid); 
		
	char test[100];
	sprintf(test,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_CONNEXION); 

	//sending process pid : mandatory to do the first connexion;
	_fd_send_query= open(test, O_WRONLY); 
	char buffer[Constante::CHAR_SIZE]; 
	sprintf(buffer,"%d", _pid);
	write(_fd_send_query, buffer, sizeof(buffer)); 
	close(_fd_send_query);
}

//utilities
void Client::communication(char *buffer){
	_fd_send_query =  open(_pipe_to_server, O_WRONLY); 
	write(_fd_send_query, buffer, Constante::CHAR_SIZE); //sending query
	close(_fd_send_query);
	_fd_get_query = open(_pipe_from_server, O_RDWR);
	if (_fd_get_query != -1){
		while(true){
			int res = read(_fd_get_query , buffer, Constante::CHAR_SIZE);
			if (res == -1){
                std::cout << " [ERROR] " <<_pid << "n'a pas reussit a lire"<<std::endl;
            }
            else{
            	break;
			}
		}
	}
	close(_fd_get_query );
}

//Communication
bool Client::signIn(char *pseudo, char *pswd, bool true_connexion){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Ma&%s&%s&%d", pseudo, pswd, _pid);
	communication(buffer);
	bool success = atoi(buffer); // 0: User doesn't exist || 1: has been connected
	if(success and true_connexion){strcpy(_pseudo, pseudo);}
	
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
	int state = atoi(buffer); // 0:request sent || 1:already in request ||2: Already Friend||3:error pseudo
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
	sprintf(buffer, "Mk&%s&%s&%d", _pseudo,pseudo, _pid);
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
	sprintf(buffer, "Mh&%s&%d", _pseudo, _pid);
	communication(buffer); 
	strcpy(res, buffer); //pseudo1|score&pseudo2|score&pseudo|score....
}

void Client::get_profile(char *res){
	char buffer[Constante::CHAR_SIZE];
	std::cout << _pseudo << std::endl;
	sprintf(buffer, "Mi&%s&%d", _pseudo,_pid);
	communication(buffer); 
	strcpy(res, buffer); //pseudo1&score
}

void Client::exit(){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "Mj&%d",_pid);
	_fd_send_query =  open(_pipe_to_server, O_WRONLY); 
	write(_fd_send_query, buffer, Constante::CHAR_SIZE);
	close(_fd_send_query);
	
}



int  Client::createGame(char *game_info){
	char buffer[Constante::CHAR_SIZE];
	sprintf(buffer, "P&%s&%d", game_info,_pid);
	communication(buffer);
}

//destructor
Client::~Client(){
	exit(); //kill process
}

std::string Client::read_game_pipe(){
	int fd;
	char buffer[Constante::CHAR_SIZE];
	fd = open(_pipe_game_sett, O_RDONLY);
	if (fd != -1){
		while(true){
			int res = read(fd , buffer, Constante::CHAR_SIZE);
			if (res == -1){}
            else{
            	break;
			}
		}
	}
	close(fd );
	
	return std::string(buffer);
}

void Client::send_game_input(int inp){

	int fd =  open(_pipe_input_game, O_WRONLY); 
	write(fd, &inp, sizeof(int)); //sending query
	close(fd);
}







