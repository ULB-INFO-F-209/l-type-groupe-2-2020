#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//#include <fcntl.h> // mode_t (permission : O_WRONLY)

class Client
{
	char *_pseudo;
	char * _pswd;
	pid_t _pid=0;
	int _id;
	char *_tube; //tube
	int fd[2]{};	//
public:
	explicit Client(char *nom_tube, char *pseudo, char *pswd, int id):
	_pseudo(pseudo), _pswd(pswd), _id(id),_tube(nom_tube){}

	void start_session(pid_t){ //boucle infini

		std::cout<<" je suis ";
		fputs(_pseudo, stdout);
		std::cout<<"\n\n";
		std::cout<<"mon mot de passe est : ";
		fputs(_pswd, stdout);
		std::cout<< " mon id est "<<_id<<std::endl;	
		std::cout << "juste utiliser fd sinon unused variable "<<fd[0]<<std::endl; 
	}

	void set_pid(pid_t pid){_pid = pid;}

	~Client()=default;
	
};


#endif