#include "server.hpp"
#include "parsing.hpp"

bool Server::_is_active = false;
Database Server::_db{};
std::mutex Server::mtx;

/**
 * Constructeur :
 *  - cree 2 pipe, connexion et reponse
 *  - lance 2 threads independant pour gerer connexion et reponse
 * 
 **/
Server::Server():_pipe_running() {

    signal(SIGINT,close_me);

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
        std::thread t3 (&Server::launch_db_save);
        t3.detach();
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
	if (input[0] == Constante::ACTION_MENU_PRINCIPAL) {
		switch(input[1]) {
			case Constante::SIGN_IN:
				resClient(&processId, signIn(input));    //Ma_pseudo_mdp
				break;					//a chaque connexion le server associe un pid a un pseudo
			case Constante::SIGN_UP:
				resClient(&processId, signUp(input));    //Mb_pseudo_mdp
				break;
			case Constante::ADD_FRIEND:
				resClient(&processId, addFriend(input)); //Mc_PseudoMe_PseudoF
				break;
			case Constante::DEL_FRIEND:
				resClient(&processId,delFriend(input)); //Md_Pseudo
				break;
			case Constante::SEND_FRIEND_REQUEST:
                resClient(&processId,sendFriendRequest(input)); //Me&source&destination&pid
				//resClient(processId, ret) avec ret le retour de checkleaderboard
				break;
			case Constante::GET_FRIEND_REQUEST:
                getFriendRequest(input);
                resClient(&processId,input); //Mf&pseudo&pid ==> get friend request
				break;
			case Constante::GET_FRIEND_LIST:
                friendList(input); // input change il contient mtn le res de friendList
                resClient(&processId,input);
				//res = getFriendRequest(input); //Mg_Pseudo
				break;
			case Constante::LEARDERBOARD:
                checkleaderboard(input); //Mh_ checkLeaderboard
                resClient(&processId,input);
				break;
			case Constante::VIEW_PROFILE:
				viewProfile(input); //Mi&pseudo  // input change il contient mtn le res de viewProfile
                resClient(&processId,input); 
				break;
            case Constante::DEL_FRIEND_REQUEST:
                resClient(&processId,delFriendRequest(input));
				//res = viewProfile(input); //Mh_Pseudo
                break;
            case Constante::CLIENT_EXIT:
                client_exit(input);
                break;
		}

		
	} else if (input[0] == Constante::GAME_SETTINGS){
        Parsing::Game_settings game_sett;
        get_game_settings(input,&game_sett);// [TODO] cette fonction lance un thread avec le jeu et les parametre du jeu
        bool o = true;
        resClient(&processId,o);
        launch_game(&game_sett);
	} else {
		std::cerr << "[ERROR IN INPUT]" << std::endl;
		return;
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
                std::cout << "[ERROR] CAN'T READ IN INIT CONNEXION" <<std::endl;
            }
            else{
                std::cout << "connexion du processus :" <<proc_id<<std::endl;

                char pipe_name[Constante::CHAR_SIZE*2];
                char pipe_input_game[Constante::CHAR_SIZE*2];
                char pipe_game[Constante::CHAR_SIZE*2];

                sprintf(pipe_name,"%s%s",Constante::BASE_PIPE_FILE,proc_id); // constitue le nom du pipe priver entre le serveur et le client
                sprintf(pipe_input_game,"%s%s",Constante::BASE_INPUT_PIPE,proc_id);
                sprintf(pipe_game,"%s%s",Constante::BASE_GAME_PIPE,proc_id);

                createPipe(pipe_name); // creation de nouveau pipe avec le pid du client
                createPipe(pipe_game);
                createPipe(pipe_input_game);

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
    mtx.lock();
    auto ret_val= _db.friendRequest(pseudoSrc, pseudoDest);
    mtx.unlock(); 
    return ret_val;
}

bool Server::addFriend(char* val){
    char pseudo1[20], pseudo2[20];
    Parsing::parsing(val, pseudo1, pseudo2);
    mtx.lock();
    auto ret_val = _db.addFriend(pseudo1, pseudo2);
    mtx.unlock(); 
    return ret_val;
}

bool Server::delFriend(char* val){
    char pseudo1[20], pseudo2[20]; 
    Parsing::parsing(val, pseudo1, pseudo2);
    mtx.lock();
    auto ret_val = _db.removeFriend(pseudo1, pseudo2);
    mtx.unlock(); 
    return ret_val;
}

void Server::checkleaderboard(char* val){ //only need a pid
    std::vector<Profile> leaderboard = _db.checkLeaderboard();
    Parsing::profile_list_to_str(val, &leaderboard);
}

void Server::friendList(char* val) {
	char pseudo[20];
    Parsing::parsing(val, pseudo);
    std::vector<Profile> friends(_db.getFriendList(pseudo));
    Parsing::profile_list_to_str(val,&friends);
}

void Server::getFriendRequest(char* val) {
	char pseudo[20];
	Parsing::parsing(val, pseudo);
    std::vector<Profile> friends(_db.getFriendRequest(pseudo));;
    Parsing::profile_list_to_str(val,&friends);
}

void Server::viewProfile(char* val) {  
	char player[20];
	Parsing::parsing(val, player);
    Parsing::Profile prof = _db.getProfile(player);
    Parsing::profile_to_str(val,prof);
}

bool Server::delFriendRequest(char* val){
    //Mk&pseudo&pseudoF&pid
    char pseudo1[20], pseudo2[20]; 
    Parsing::parsing(val, pseudo1, pseudo2);
    mtx.lock();
    auto ret_val = _db.delFriendRequest(pseudo1,pseudo2);
    mtx.unlock();
    return ret_val;
}

/**
 * Envoie la réponse au bon client
 * 
 **/ 
void Server::resClient(std::string* processId, bool res) {
	char message[Constante::CHAR_SIZE];int fd;
    sprintf(message, "%d", res);

    char pipe_name[Constante::CHAR_SIZE];
    sprintf(pipe_name,"%s%s%s", Constante::PIPE_PATH, Constante::BASE_PIPE_FILE,(*processId).c_str());


	fd = open(pipe_name,O_RDWR);
    if (fd != -1) write(fd, &message, Constante::CHAR_SIZE);
    else std::cout << "[ERROR] requete non ecrite " << std::endl;
    
    close(fd);
    std::cout << "resultat requete : " << message <<" sur le pipe "<<pipe_name << std::endl; 
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

void Server::resClient(std::string* processId, int res) {
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

/**
 * @brief (deamons) lance un sauvergarde periodique (90 sec en theorie) de la database
 * 
 */
void Server::launch_db_save(){
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(Constante::SERVER_SAVE_TIME));
        mtx.lock();
        _db.dbSave(); 
        mtx.unlock(); 
    }
}

/**
 * @brief Supprime les pipes du client [TODO] ajouter la sup du pipe input et game
 * 
 * @param input : le pid du client pour pouvoir supprimer les pipes
 */
void Server::client_exit(char *input){

    std::string processId(input);
    int i = processId.rfind(Constante::DELIMITEUR);
    processId = processId.substr(i+1,processId.length());

    processId.insert(0,Constante::BASE_PIPE_FILE);
    processId.insert(0,Constante::PIPE_PATH);

    if(remove(processId.c_str()) != 0){
        std::cerr << "[ERROR] suppresion du pipe : " << processId << std::endl;
    }
    else{
        std::cout << processId << " supprimer avec succes :) "<<std::endl;
    }

}

/**
 * @brief recoit les parametres de jeu et lance un thread avec le jeu
 * 
 * @param input les parametres non parser
 */
void Server::get_game_settings(char* input, Parsing::Game_settings* game_sett){
	
	Parsing::create_game_from_str(input, game_sett);
	std::cout << game_sett->nb_player << "-" << game_sett->pseudo_hote << "-"
			  << game_sett->pseudo_other    << "-" << game_sett->drop_rate << "-"
			  << game_sett->ally_shot << "-" << game_sett->nb_lives << "-"
			  << game_sett->difficulty_str << std::endl;

    std::string processId(input);
    int i = processId.rfind(Constante::DELIMITEUR);
    processId = processId.substr(i+1,processId.length());
    strcpy(game_sett->pid,processId.c_str());
    
    return;
}

void Server::launch_game(Game_settings* sett_game){

    CurrentGame game{*sett_game};

    char input_pipe[Constante::CHAR_SIZE],send_response_pipe[Constante::CHAR_SIZE];
    sprintf(input_pipe,"%s%s%s",Constante::PIPE_PATH,Constante::BASE_INPUT_PIPE,sett_game->pid);
    sprintf(send_response_pipe,"%s%s%s",Constante::PIPE_PATH,Constante::BASE_GAME_PIPE,sett_game->pid);

    std::cout << input_pipe << std::endl << send_response_pipe << std::endl;
    bool gameOn = true;
    while(gameOn){
        
        int inp = read_game_input(input_pipe);
        std::string resp = game.run_server(inp);
        resClient(send_response_pipe,&resp);
    }
    std::cout << "while fin"<< std::endl;
}

void Server::resClient(char* pipe, std::string* res){
    char to_send[Constante::CHAR_SIZE];
    strcpy(to_send,res->c_str());
    
    int fd = open(pipe,O_WRONLY);
    if (fd != -1) write(fd, to_send, sizeof(Constante::CHAR_SIZE));
    else std::cout << "[ERROR] settings non ecrit " << std::endl;
    close(fd);
}

int Server::read_game_input(char * pipe){
    int message;
    int fd =open(pipe, O_RDONLY);
    if (fd != -1){
        int val = read(fd,&message,sizeof(int)); // TODO verification de val 
        
        if (val == -1){
            std::cout << "[ERROR] CAN'T READ IN INPUT PIPE " <<std::endl;
        }
        
    }
    else{
        std::cerr << "[ERROR PIPE INPUT]" <<std::endl;
    }
    close(fd);
    return message;

}


















