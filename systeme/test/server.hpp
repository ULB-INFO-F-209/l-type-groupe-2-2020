#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>


#include <sys/types.h>
#include <sys/stat.h>
//#include <fcntl.h> // mode_t (permission : O_WRONLY)
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "client.hpp"

class Server
{
	static const int _nb_clients_max =10;
	int _nb_client_courant = 0;
	Client *_clients_connectee[_nb_clients_max];
	char *_pipes[_nb_clients_max];
public:
	explicit Server()=default;
	void connect_client(char *pseudo, char*pswd){
		
		mkfifo(pseudo,0666); //voir les mode d'accé
		Client * x = new Client(pseudo, pseudo, pswd, _nb_client_courant);
		_clients_connectee[_nb_client_courant] = x;
		_pipes[_nb_client_courant] = pseudo;
		_nb_client_courant ++;
		pid_t new_process = fork();
		if(new_process==0){//fils
			system("xterm");
			x->start_session(new_process);
		}
	}

	void start_server(){
		while(1){
			connexion();
		}
	}

	void connexion(){
		system("clear");
		char pseudo[60]; char pswd[60];
		std::cout << "\n\n"<<"Entrez un pseudo >> ";
		fgets(pseudo, 60, stdin);
		std::cout <<"\n\n"<<"Entrez un mot de passe >> ";
		fgets(pswd, 60, stdin);
		connect_client(pseudo, pswd);
	}

	~Server(){
		for (int i = 0; i < _nb_client_courant; ++i){
			delete _clients_connectee[i];
		}
	}
	
};



#endif