#include "server.hpp"
#include "Constante.hpp"

bool Server::_is_active = false;
std::vector<Server* > Server::_server_instance{};

Server::Server():_pipe_running(),_SERVER_PID(getpid())/*,_db()*/{

    std::cout << "LANCEMENT DU SERVEUR \n";
    if (!isServerActive()){ // pas actif

        createPipe(Constante::PIPE_DE_CONNEXION);

        _server_instance.push_back(this);
        signal(SIGUSR1,handleSignalCall);

        std::cout << "Serveur connecter ... \n";
        _is_active = true;
        std::thread t1(&Server::initConnexions,this); // thread d'ecoute (deamon)
        t1.detach(); //TODO verifier le comportement de ca 
    }
    else{
        std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl; 
        exit(1);
    }
    pause();
    
}


void Server::handleSignalCall(int signb){

    std::cout << "Signale recu " << std::endl;
    int fd; char message[Constante::CHAR_SIZE];
    for(int i = 0; i < ((_server_instance[0])->_pipe_running).size(); i++){ 

        const char * private_pipe_name = ((_server_instance[0])->_pipe_running)[i]; // recuparation du pipe stocker
        std::cout << "lancement du pipe : " << private_pipe_name << std::endl;
        fd =open(private_pipe_name, O_RDONLY);

        if (fd != -1){
            int val = read(fd,message,Constante::CHAR_SIZE);

            std::thread t1(&Server::catchInput,_server_instance[0],message);
            t1.detach();
        }
        else{
            std::cerr << "[ERROR AVEC LE PIPE : "<< private_pipe_name<<"]" << std::endl;
        }
        
    }

}

void Server::handleClientPipe(const char * input){


}

void Server::catchInput(char * input) {
	//char input[Constante::CHAR_SIZE]; //input[0] = M pour menu et J pour jeu
	bool res = false;

	if (input[0] == Constante::ACTION_MENU_PRINCIPAL[0]) {
		switch(input[1]) {
			case Constante::ACTION_MENU_PRINCIPAL[1]:
				res = signIn(input);    //Ma-Pseudo-MDP-PID
				break;					//a chaque connexion le server associe un pid a un pseudo
			case Constante::ACTION_MENU_PRINCIPAL[2]:
				res = signUp(input);    //Mb-Pseudo-MDP-PID
				break;
			case Constante::ACTION_MENU_PRINCIPAL[3]:
				res = addFriend(input); //Mc-Pseudo-PID
				break;
			case Constante::ACTION_MENU_PRINCIPAL[4]:
				res = delFriend(input); //Md-Pseudo-PID
				break;
			case Constante::ACTION_MENU_PRINCIPAL[5]:
				checkleaderboard(input);//Me-PID
				//resClient(processId, ret) avec ret le retour de checkleaderboard
				break;
		}

		std::string processId(input); 
    	int i = processId.rfind(Constante::DELIMITEUR);
    	processId = processId.substr(i+1,processId.length()); //pour recup le PID
    	resClient(&processId, res);
	}
	
	else if (input[0] == Constante::ACTION_JEU[0]){
		//similaire a M mais on a besoin de connaitre les input du jeu
	}
	else {
		std::cerr << "[ERROR IN INPUT]" << std::endl;
		exit(1);
	}

}

void Server::createPipe(const char *name){

    char path[Constante::CHAR_SIZE];
    sprintf(path,"%s%s",Constante::PIPE_PATH,name);

    if (int ret_val = mkfifo(path,0666) > 1 ){ // gestion des erreurs

        std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
        exit(1);
    }
    else{
        std::cout << "creation du pipe : " << path <<std::endl;
    }
    _pipe_running.push_back(name);
}

void Server::initConnexions(){

    int fd;
    char proc_id[Constante::CHAR_SIZE], connex_pipe_path[Constante::CHAR_SIZE], message[Constante::CHAR_SIZE];
    sprintf(connex_pipe_path,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_CONNEXION);

    while (true){
        std::cout << std::endl;
        fd =open(connex_pipe_path, O_RDONLY);
        if (fd != -1){
            int val = read(fd,proc_id,Constante::CHAR_SIZE); // TODO verification de val 
            std::cout << "connexion du processus :" <<proc_id<<std::endl;

            char pipe_name[Constante::CHAR_SIZE*2];
            sprintf(pipe_name,"%s%s",Constante::BASE_PIPE_FILE,proc_id); // constitue le nom du pipe priver entre le serveur et le client
            
            createPipe(pipe_name); // creation de nouveau pipe avec le pid du client
            close(fd);

            /**                            TODO 
             * mettre tout ce qu'il y en dessous dans un thread sinon ce thread est bloqué ... 
             *
             **/
            char pipe_path[Constante::CHAR_SIZE*3];
            sprintf(pipe_path,"%s%s",Constante::PIPE_PATH,pipe_name);

            // ecire le pid du serveur sur le pipe connexion
            sprintf(message,"%d",_SERVER_PID);
            sleep(5);
            printf("Jai ecris mon pid  : %d sur %s\n",_SERVER_PID,pipe_path);
            while (true)
            {
                int fd2 = open(pipe_path,O_WRONLY);
                if (fd2 != -1){
                    write(fd2,message,strlen(message)+1);
                    break;
                }
                close(fd2);
            }
            
            
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
	char message;int fd;
    message = res;
	
    char pipe_name[Constante::CHAR_SIZE];
    sprintf(pipe_name,"%s%s",Constante::BASE_PIPE_FILE,(*processId).c_str());

	fd = open(pipe_name,O_WRONLY);

    if (fd != -1){
        write(fd,&message,strlen(&message)+1);
    }
    else{
        printf("pas de connexion\n");
    }
    close(fd);
}



