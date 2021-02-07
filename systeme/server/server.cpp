#include "server.hpp"

bool Server::_is_active = false;

Server::Server(){

    std::cout << "LANCEMENT DU SERVEUR \n";
    if (!isServerActive()){ // pas actif
        createPipe("connexion");
        std::cout << "Serveur connecter ... \n";
        _is_active = true;
        std::thread(initConnexions); // thread d'ecoute (deamon)
    }
    else{
        std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl; 
        exit(1);
    }
    pause();
}

void Server::catchInput() {
	char input[100]; //input[0] = M pour menu et J pour jeu
	bool res = false;
	if (input[0] == 'M') {
		switch(input[1]) {
			case 'a':
				res = signIn(input);    //Ma-Pseudo-MDP-PID
				break;					//a chaque connexion le server associe un pid a un pseudo
			case 'b':
				res = signUp(input);    //Mb-Pseudo-MDP-PID
				break;
			case 'c':
				res = addFriend(input); //Mc-Pseudo-PID
				break;
			case 'd':
				res = delFriend(input); //Md-Pseudo-PID
				break;
			case 'e':
				checkleaderboard(input);//Me-PID
				//resClient(processId, ret) avec ret le retour de checkleaderboard
				break;
		}
		std::string processId(input); 
    	int i = processId.rfind("-");
    	processId = processId.substr(i+1,processId.length()); //pour recup le PID
    	resClient(&processId, res);
	}
	
	else if (input[0] == 'J'){
		//similaire a M mais on a besoin de connaitre les input du jeu
	}
	else {
		std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl;
		exit(1);
	}

}

void Server::createPipe(const char *name){

    
    if (int ret_val = mkfifo(name,0666) > 1 ){ // gestion des erreurs

    std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
    exit(1);
    }
    else{
        std::cout << "creation du pipe : " << name <<std::endl;
    }
    _pipe_running.push_back(name);
}

void Server::initConnexions(){

    int fd;
    char proc_id[100];
   
    while (true){
        fd =open("connexion", O_RDONLY);
        if (fd != -1){
            int val = read(fd,proc_id,100);
            std::cout << "connexion du processus :" <<proc_id<<std::endl;
            char pipe_name[]= {"pipefile_"};
            strcat(pipe_name, proc_id);

            createPipe(pipe_name); // creation de nv pipe avce le pid du client
            close(fd);

            //break;
            
        }
        
    }
    
}

void Server::sendPositionBoard(){
    return ;
}

bool Server::signIn(char* val){
    return false;
}

bool Server::signUp(char* val){
    return false;
}

bool Server::addFriend(char* val ){
    return false;
}

bool Server::delFriend(char* val ){
    return false;
}

void Server::checkleaderboard(char* ){
    return ;
}

void Server::resClient(std::string* processId, bool res) {
	char message;
    message = res;
	int fd;
    char pipe_name[100] ;
    sprintf(pipe_name,"pipefile_%s",(*processId).c_str());
	fd = open(pipe_name,O_WRONLY);
    if (fd != -1){
        write(fd,&message,strlen(&message)+1);
    }
    else{
        printf("pas de connexion\n");
    }
    close(fd);
}



