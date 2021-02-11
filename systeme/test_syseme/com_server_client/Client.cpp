#include "Client.hpp"

/*
	Notes : 
		sending and reading has to be in one function (repetions)
*/

//constructor
Client::Client(){
	pid_t pid_process = getpid();
	sprintf(_get_query,"%s%s%d",Constante::PIPE_PATH,Constante::BASE_PIPE_FILE, pid_process); //nom a lire
	strcpy(_send_query,Constante::PIPE_DE_REPONSE); //pipe où écrire

	//sending process pid;
	_fd_g= open(Constante::PIPE_DE_CONNEXION, O_WRONLY); 
	char buffer[100]; 
	sprintf(buffer,"%d", pid_process);
	write(_fd_g, buffer, sizeof(buffer)); 
	close(_fd_g);
	std::cout <<" I send  "<<buffer<<std::endl;

	//open other pipe
	_fd_s = open(_send_query, O_WRONLY);
}

//
void Client::communication(char *buffer){
	write(_fd_s, buffer, sizeof(buffer)); //sending query
	read(_fd_g, buffer,  sizeof(buffer)); //getting feedback
}
//getters || setters
bool Client::signUp(char *pseudo, char *pswd){
	char buffer[100];
	sprintf(buffer, "Mb&%s&%s", pseudo, pswd);
	communication(buffer);
	bool success = atoi(buffer); // 0: pseudo already taked || 1:new account had been created

	return success; 

}
bool Client::signIn(char *pseudo, char *pswd){
	char buffer[100];
	sprintf(buffer, "Ma&%s&%s", pseudo, pswd);
	communication(buffer);
	bool success = atoi(buffer); // 0 or 1 

	return success; 
}
int Client::addFriend(char *p_friend){
	char buffer[100];
	sprintf(buffer, "Mc&%s&%s", _pseudo, p_friend);
	communication(buffer);
	int state = atoi(buffer); // 0 , 1, 2 = sent, already friend, pseudo error

	return state; 
}
int Client::delFriend(char *p_friend){
	char buffer[100];
	sprintf(buffer, "Md&%s&%s", _pseudo, p_friend);
	communication(buffer);
	int state = atoi(buffer); // 0 , 1, 2 = deleted, not friend yet, pseudo error

	return state; 

}
void  Client::getFriendRequest(char *res){
	char buffer[100];
	sprintf(buffer, "Mg&%s", _pseudo);
	communication(buffer);
	strcpy(res, buffer); //retour res
}
void Client::checkLeaderboard(char * res){
	char buffer[100] = "Me"; //increase size ! 
	write(_fd_s, buffer, sizeof(buffer)); 
	read(_fd_g, buffer,  sizeof(buffer)); 
	strcpy(res, buffer); //retour res
};
int  Client::createGame(char *second_player){
	char buffer[100];
	sprintf(buffer, "P&%s&%s", _pseudo, second_player);
	communication(buffer);
	int ID_game = atoi(buffer);

	return ID_game;
}
void Client::log_out(){
	char buffer[100] = "Mi";
	write(_fd_s, buffer, sizeof(buffer)); //sending alerte 
	close(_fd_s);
	//the server should delete all pipe we use!
	//and destruct my game if I was playing
}

Client::~Client(){
	log_out();
}
