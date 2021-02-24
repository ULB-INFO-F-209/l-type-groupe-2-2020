#include "server.hpp"
#include "Constante.hpp"
#include "parsing.hpp"

bool Server::_is_active = false;

/**
 * Constructeur :
 *  - cree 2 pipe, connexion et reponse
 *  - lance 2 threads independant pour gerer connexion et reponse
 * 
 **/
Server::Server():_pipe_running() ,_db(){

    std::cout << "LANCEMENT DU SERVEUR \n";
    if (!isServerActive()){ // pas actif

        _db.dbLoad();

        createPipe(Constante::PIPE_DE_CONNEXION);
        createPipe(Constante::PIPE_DE_REPONSE);

        //_server_instance.push_back(this);
        //signal(SIGUSR1,handleSignalCall);

        std::cout << "\nServeur connecter ... \n";
        _is_active = true;
        std::thread t1(&Server::initConnexions,this); // thread d'ecoute (deamon)
        t1.detach(); //TODO verifier le comportement de ca 
        std::thread t2(&Server::handleIncommingMessages,this);
        t2.detach();
    }
    else{
        std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl; 
        exit(1);
    }
    pause();
    
}

/**
 * Ecoute le pipe de reponse et cree un nouveau thread(catchInput) pour gerer 
 * l'input et envoyer la reponse
 * 
 **/
void Server::handleIncommingMessages(){
    

    char response_pipe_path[Constante::CHAR_SIZE],message[Constante::CHAR_SIZE];
    sprintf(response_pipe_path,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_REPONSE);

    int fd, val;
    
    
    while (true){
        
        fd =open(response_pipe_path, O_RDONLY);
        if (fd < 0){
            std::cerr << "[ERROR OPENING PIPE("<<response_pipe_path<<")]" <<std::endl;
            exit(-1);
        }

        val = read(fd,message,Constante::CHAR_SIZE);
        if (val < 0){
            std::cerr << "[ERROR READING PIPE("<<response_pipe_path<<")]" <<std::endl;
            //exit(-1);
        }
        else if (val >= 0){
            //char *message2 = message;
        
            std::thread t1(&Server::catchInput,this,message); // thread de reponse 
            t1.detach();
        }
        close(fd);
    }
    close(fd);
}

/**
 * gere les messages client et envoie la reponse au bon client
 * 
 **/
void Server::catchInput(char* input) {
	//char input[Constante::CHAR_SIZE]; //input[0] = M pour menu et J pour jeu
    std::string processId(input);
    int i = processId.rfind(Constante::DELIMITEUR);
    processId = processId.substr(i+1,processId.length());

    std::cout << "Input recu : " << input <<std::endl;
	if (input[0] == Constante::ACTION_MENU_PRINCIPAL[0]) {
		switch(input[1]) {
			case Constante::ACTION_MENU_PRINCIPAL[1]:
				resClient(&processId, signIn(input));    //Ma_pseudo_mdp
				break;					//a chaque connexion le server associe un pid a un pseudo
			case Constante::ACTION_MENU_PRINCIPAL[2]:
				resClient(&processId, signUp(input));    //Mb_pseudo_mdp
				break;
			case Constante::ACTION_MENU_PRINCIPAL[3]:
				resClient(&processId, addFriend(input)); //Mc_PseudoMe_PseudoF
				break;
			case Constante::ACTION_MENU_PRINCIPAL[4]:
				//res = delFriend(input); //Md_Pseudo
				break;
			case Constante::ACTION_MENU_PRINCIPAL[5]:
				checkleaderboard(input); //Me
				//resClient(processId, ret) avec ret le retour de checkleaderboard
				break;
			case Constante::ACTION_MENU_PRINCIPAL[6]:
				resClient(&processId,friendList(input)); //Mf_Pseudo
				break;
			case Constante::ACTION_MENU_PRINCIPAL[7]:
				//res = getFriendRequest(input); //Mg_Pseudo
				break;
			case Constante::ACTION_MENU_PRINCIPAL[8]:
				//res = sendFriendRequest(input); //Mj_Pseudo
				break;
			case Constante::ACTION_MENU_PRINCIPAL[9]:
				//res = viewProfile(input); //Mh_Pseudo
				break;
		}

		
	} else if (input[0] == Constante::ACTION_JEU[0]){
		//similaire a M mais on a besoin de connaitre les input du jeu
	} else {
		std::cerr << "[ERROR IN INPUT]" << std::endl;
		exit(1);
	}

}

/**
 * Cree des pipes dans le dossier /tmp
 * 
 * format du pipe : /tmp/pipefile_name
 **/
void Server::createPipe(const char *name){
    char path[Constante::CHAR_SIZE];
    sprintf(path,"%s%s",Constante::PIPE_PATH,name);
    int ret_val = mkfifo(path,Constante::PIPE_MODE);
    std::cout << "nom pipe = " << path<<" ("<<ret_val<<"),  ";
    
    if (errno == EEXIST ){ //cree le pipe
        std::cout << "pipe " << path << " existe deja" << std::endl;
        
    }
    else if(ret_val == -1){
        std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
        exit(1);
    }
    else{
        std::cout << "creation du pipe : " << path <<std::endl;
    }
    _pipe_running.push_back(name);
}

/**
 * (deamon)
 * Ecoute constament le pipe connexion et cree les autres pipes 
 * en consequence
 **/
void Server::initConnexions(){

    int fd;
    char proc_id[Constante::CHAR_SIZE], connex_pipe_path[Constante::CHAR_SIZE], message[Constante::CHAR_SIZE];
    sprintf(connex_pipe_path,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_CONNEXION);

    while (true){
        std::cout << std::endl;
        fd =open(connex_pipe_path, O_RDONLY);
        if (fd != -1){
            int val = read(fd,proc_id,Constante::CHAR_SIZE); // TODO verification de val 
            if (val == -1)
            {
                std::cout << "connexion echouée" <<proc_id<<std::endl;
            }
            else{
            std::cout << "connexion du processus :" <<proc_id<<std::endl;

            char pipe_name[Constante::CHAR_SIZE*2];
            sprintf(pipe_name,"%s%s",Constante::BASE_PIPE_FILE,proc_id); // constitue le nom du pipe priver entre le serveur et le client
            
            createPipe(pipe_name); // creation de nouveau pipe avec le pid du client
            close(fd);
            }
    
        }
        else{
            std::cerr << "[ERROR PIPE CONNEXION]" <<std::endl;
        }


    }

}
            
void Server::sendPositionBoard(){
    return ;
}

bool Server::signIn(char* val){
    char pseudo[20], pswd[20];
    Parsing::parsing(val, pseudo, pswd); // need val to be val[100] 
    return _db.verifyLogin(pseudo, pswd);
}

bool Server::signUp(char* val){
    char pseudo[20], pswd[20];
    Parsing::parsing(val, pseudo, pswd);
    return _db.createAccount(pseudo, pswd);
}

int Server::sendFriendRequest(char* val){
    char pseudoSrc[20], pseudoDest[20];
    Parsing::parsing(val, pseudoSrc, pseudoDest);
    return _db.friendRequest(pseudoSrc, pseudoDest);
}

bool Server::addFriend(char* val){
    char pseudo1[20], pseudo2[20];
    Parsing::parsing(val, pseudo1, pseudo2);
    return _db.addFriend(pseudo1, pseudo2);
}

bool Server::delFriend(char* val){
    char pseudo1[20], pseudo2[20]; 
    Parsing::parsing(val, pseudo1, pseudo2);
    return _db.removeFriend(pseudo1, pseudo2);
}

void Server::checkleaderboard(char* val){ //only need a pid
    std::vector<Profile> leaderboard = _db.checkLeaderboard();
    return ;
}


char* Server::friendList(char* val) {
	char pseudo[20],buffer[Constante::CHAR_SIZE];
    Parsing::parsing(val, pseudo);
    std::vector<char*> friends = _db.getFriendList(pseudo);
    Parsing::profile_list_to_str(buffer,&friends);
    std::cout << "tema : " << buffer <<std::endl;
    return buffer;
}

bool Server::getFriendRequest(char* val) {
	char pseudo[20];
	Parsing::parsing(val, pseudo);
    std::vector<char*> requests = _db.getFriendRequest(pseudo);
    return true;
}

bool Server::viewProfile(char* val) {  //only need a pid ? the name ?
	char player[20];
	Parsing::parsing(val, player);
    Profile prof = _db.getProfile(player);
    return true;
}


/**
 * Envoie la réponse au bon client si la réponse est un booléen
 * 
 **/ 
void Server::resClient(std::string* processId, bool res) {
	char message[Constante::CHAR_SIZE];int fd;
    sprintf(message, "%d", res);

    char pipe_name[Constante::CHAR_SIZE];
    sprintf(pipe_name,"%s%s%s", Constante::PIPE_PATH, Constante::BASE_PIPE_FILE,(*processId).c_str());

    std::cout << "resultat requete : " << message <<" sur le pipe "<<pipe_name << std::endl; 

	fd = open(pipe_name,O_WRONLY);
    if (fd != -1) write(fd, &message, Constante::CHAR_SIZE);
    else std::cout << "[ERROR] requete non ecrite " << std::endl;
    
    close(fd);
    std::cout <<std::endl;
}

void Server::resClient(std::string* processId, char* res) {
	int fd;

    char pipe_name[Constante::CHAR_SIZE];
    sprintf(pipe_name,"%s%s%s", Constante::PIPE_PATH, Constante::BASE_PIPE_FILE,(*processId).c_str());

    std::cout << "resultat requete : " << res <<" sur le pipe "<<pipe_name << std::endl; 

	fd = open(pipe_name,O_WRONLY);
    if (fd != -1) write(fd, res, Constante::CHAR_SIZE);
    else std::cout << "[ERROR] requete non ecrite " << std::endl;
    
    close(fd);
    std::cout <<std::endl;
}



