#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h> // mode_t (permission : O_WRONLY)

class Client
{
	char *_pseudo;
	char * _pswd;
	pid_t _pid;
	int _id;
	char *_tube; //tube
	int fd;	//
public:
	//constructor
	explicit Client(char *nom_tube):_tube(nom_tube){}
	explicit Client(char *nom_tube, char *pseudo, char *pswd, int id):
	_pseudo(pseudo), _pswd(pswd), _id(id){}

	void start_session(pid_t){ //boucle infini
		std::cout <<" je suis "<<_pseudo<<std::endl;
		std::cout <<"mon mot de passe est : "<<_pswd<<std::endl;
		std::cout << " mon id est "<<_id<<std::endl;
		fd = open(_pseudo, O_WRONLY); //mask unused variable
	}

	void set_pid(pid_t pid){_pid = pid;}

	~Client()=default;
	
};


#endif