#include "server.hpp"

#define TEST_GAME1
#define DEBUG_GAME
bool Server::_is_active = false;
Database Server::_db{};
std::mutex Server::mtx;
std::mutex Server::mtx_game;
std::vector<Server::PIDinGame*> Server::_pipe_running{};


/**
 * @brief Construct a new Server:: Server object
 * 
 */
Server::Server(){

    signal(SIGINT,close_me); // gestion du CTRL + C ==> save db 
    signal(SIGPIPE, error_pip); // redirection du signal SIGPIPE vers SIG_IGN pour l'ignorer 
    
    if (!isServerActive()){ // pas actif

        _db.dbLoad();

        createPipe(Constante::PIPE_DE_CONNEXION);
        createPipe(Constante::PIPE_DE_REPONSE);
        
        _is_active = true;
        std::thread t1(&Server::initConnexions,this); // thread d'ecoute de connex (deamon)
        t1.detach();
        std::thread t2(&Server::handleIncommingMessages,this); // thread d'ecoute des requetes (deamon)
        t2.detach();
        std::thread t3 (&Server::launch_db_save); // thread de sauvegarde (deamon)
        t3.detach();
    }
    else{
        std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl; 
        exit(1);
    }
    std::cout << "\n\n -----------------------|      SERVEUR PRET      |----------------------- \n\n";
    pause(); // attendre un signal  generalement CTRL+C 
    
}

/**
 * Ecoute le pipe de reponse et cree un nouveau thread(catchInput) pour gerer 
 * l'input et envoyer la reponse
 * 
 **/
void Server::handleIncommingMessages(){
    
    int fd, val;
    char response_pipe_path[Constante::CHAR_SIZE],message[Constante::CHAR_SIZE];
    sprintf(response_pipe_path,"%s%s",Constante::PIPE_PATH,Constante::PIPE_DE_REPONSE);

    while (true){
        fd =open(response_pipe_path, O_RDONLY);
        if (fd < 0){
            std::cerr << "[ERROR OPENING PIPE("<<response_pipe_path<<")]" <<std::endl;
            //exit(-1);
        }

        val = read(fd,message,Constante::CHAR_SIZE);
        if (val < 0){
            std::cerr << "[ERROR READING PIPE("<<response_pipe_path<<")]" <<std::endl;
            //exit(-1);
        }
        else if (val >= 0){
        
            std::thread t1(&Server::catchInput,this,message); // thread de reponse 
            t1.detach();
        }
        close(fd);
    }
}

/**
 * gère les messages client et envoie la reponse au bon client
 * 
 **/
void Server::catchInput(char* input) {
	
    std::string processId(input);
    int i = processId.rfind(Constante::DELIMITEUR);
    processId = processId.substr(i+1,processId.length()); //pid
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
                break;
            case Constante::CLIENT_EXIT:
                client_exit(&processId);
                break;
		}		
	} else if (input[0] == Constante::GAME_SETTINGS){
        Parsing::Game_settings game_sett;
        get_game_settings(input,&game_sett); 
        resClient(&processId,Constante::GAME_CAN_BE_LAUNCH);

        mtx_game.lock();
        for(auto p: _pipe_running){ // mettre l'état du jeu pour le pid à true
            if(processId == p->pid){
                p->in_game=true;
                break;
            }
        }
        mtx_game.unlock(); 

        std::thread t5(&Server::launch_game,this,&game_sett); // thread du jeu
        t5.detach();

	}
    else if (input[0] == Constante::LEVEL){
        switch(input[1]){
        case Constante::SAVE_LEVEL:{
            std::string level_input(input);
            std::string pseudo = level_input.substr(level_input.rfind("|")+1,level_input.rfind(Constante::DELIMITEUR));
            pseudo = pseudo.substr(0, pseudo.find(Constante::DELIMITEUR));
            
            //level name
            std::size_t idx = level_input.find('|');
            std::string player_zone = level_input.substr(0,idx);

            idx = player_zone.find("_");
            std::string lettre = player_zone.substr(0,idx);
            player_zone = player_zone.substr(idx+1, player_zone.size());

            idx = player_zone.find("_");
            std::string name_level = player_zone.substr(0,idx);

            // delete name & pid at the end
            idx = level_input.rfind("|");
            level_input = level_input.substr(0, idx);

            std::cout << "name level = " << name_level << std::endl;
            std::cout << "level = " << level_input << std::endl;

            _db.add(pseudo, level_input, name_level, 0);
            resClient(&processId,Constante::ALL_GOOD);
            break;
        }

        case Constante::LOAD_LEVEL:

            break;
        }
    }
     else {
		std::cerr << "[ERROR IN INPUT 1]" << std::endl;
		return;
	}

}

/**
 * Cree des pipes dans le dossier /tmp
 * 
 * 
 **/
void Server::createPipe(const char *name){
    char path[Constante::CHAR_SIZE];
    sprintf(path,"%s%s",Constante::PIPE_PATH,name);

    int ret_val = mkfifo(path,Constante::PIPE_MODE);
    
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
            int val = read(fd,proc_id,Constante::CHAR_SIZE);
            if (val == -1)
            {
                std::cout << "[ERROR] CAN'T READ IN INIT CONNEXION" <<std::endl;
            }
            else{
                std::cout << "connexion du processus :" <<proc_id<<std::endl;

                char pipe_name[Constante::CHAR_SIZE*2];
                char pipe_input_game[Constante::CHAR_SIZE*2];
                char pipe_game[Constante::CHAR_SIZE*2];

                PIDinGame tmp(proc_id);
                
                _pipe_running.push_back(&tmp);
                std::cout << _pipe_running[0]->pid << std::endl;
                
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
    else std::cerr << "[ERROR] requete non ecrite " << std::endl;
    
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
    else std::cerr << "[ERROR] requete non ecrite " << std::endl;
    
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
    else std::cerr << "[ERROR] requete non ecrite " << std::endl;
    
    close(fd);
    std::cout <<std::endl;
}

/**
 * @brief (deamons) lance une sauvergarde periodique (90 sec en theorie) de la database
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
 * @brief Supprime les pipes du client
 * 
 * @param input : le pid du client pour pouvoir supprimer les pipes
 */
void Server::client_exit(std::string *pid){
    std::cout << "\n\nDEPART DU CLIENT :" <<*pid << std::endl<<std::endl;
    std::string processId(*pid); 
    std::string game_pipe = *pid;
    std::string input_pipe = *pid;
    processId.insert(0,Constante::BASE_PIPE_FILE);
    game_pipe.insert(0,Constante::BASE_GAME_PIPE);
    input_pipe.insert(0,Constante::BASE_INPUT_PIPE);
    processId.insert(0,Constante::PIPE_PATH);
    input_pipe.insert(0,Constante::PIPE_PATH);
    game_pipe.insert(0,Constante::PIPE_PATH);
    
    mtx.lock();
    for(size_t i = 0; i < _pipe_running.size();i++){
        if(_pipe_running.at(i)->in_game && strcmp(_pipe_running.at(i)->pid, pid->c_str()) == 0 ){
            
            kill_process(input_pipe.c_str());
            _pipe_running.erase(_pipe_running.cbegin()+i);
            break;
        }
    }
    mtx.unlock();

    remove_pipe(processId);
    remove_pipe(game_pipe);
    remove_pipe(input_pipe);
    
}

/**
 * @brief Envoie sur le pipe en parametre Constante::CLIENT_LEAVE_GAME
 *        ce qui indique qu'un client est parti 
 *        [TODO] verifier les erreurs
 * 
 * @param pipe : le nom du pipe
 */
void Server::kill_process(const char* pipe){
    int fd = open(pipe,O_WRONLY);
    if (fd != -1) write(fd, &Constante::CLIENT_LEAVE_GAME, sizeof(int));
    else std::cerr << "[ERROR] KILL PROCESS " << std::endl;
    close(fd);
}


/**
 * @brief supprime les pipes
 * 
 * @param the_pipe : le pipe a supprimer
 */
void Server::remove_pipe(std::string the_pipe){

    if(remove(the_pipe.c_str()) != 0){
        std::cerr << "[ERROR] suppresion du pipe : " << the_pipe << std::endl;
    }
    else{
        std::cout << the_pipe << " supprimer avec succes "<<std::endl;
    }
}


/**
 * @brief recoit les paramètres de jeu et lance un thread avec le jeu
 * 
 * @param input les paramètres non parser
 */
void Server::get_game_settings(char* input, Parsing::Game_settings* game_sett){
	
	Parsing::create_game_from_str(input, game_sett);
    #ifdef DEBUG_GAME
	std::cout <<std::endl<< game_sett->nb_player << "-" << game_sett->pseudo_hote << "-"
			  << game_sett->pseudo_other    << "-" << game_sett->drop_rate << "-"
			  << game_sett->ally_shot << "-" << game_sett->nb_lives << "-"
			  << game_sett->difficulty_str <<"-"<< game_sett->pid <<std::endl;
    #endif

}

/**
 * @brief Lance une version du jeu avec les bon parametre,
 *        envoie a traver 1 pipes les objets a affiché
 *        et recoit a travers un autre pipe les inpupts  
 * 
 * @param sett_game : les settings du jeu
 */
void Server::launch_game(Parsing::Game_settings* sett_game){

    char input_pipe[Constante::CHAR_SIZE],send_response_pipe[Constante::CHAR_SIZE];
    bool gameOn=true;int inp[11];
    
    // mise en place des pipes
    sprintf(input_pipe,"%s%s%s",Constante::PIPE_PATH,Constante::BASE_INPUT_PIPE,sett_game->pid);
    sprintf(send_response_pipe,"%s%s%s",Constante::PIPE_PATH,Constante::BASE_GAME_PIPE,sett_game->pid);
    
    // test du jeu en terminale ne fonction pas avec la gui
    #ifdef TEST_GAME
        DisplayGame interface_game;
	    interface_game.init();
    #endif

    CurrentGame game{*sett_game};
    std::string resp;

    while(gameOn){
        int state = read_game_input(input_pipe, inp);  
        if(state == Constante::ERROR_PIPE_GAME || state == Constante::CLIENT_LEAVE_GAME){
            // Le client est parti ou alors le pipe a été supprimer 
            std::cout << sett_game->pid << " A LA PROCHAINE "<<std::endl;
            return;
        }
        resp = game.run_server(inp);                                                        //  le jeu du server
        if(resp == Constante::GAME_END){  // if game over
            gameOn=false;
        }
        resClient(send_response_pipe,&resp);
        usleep(10000); // 10 ms

        #ifdef TEST_GAME  // test l'affichage jeu/client 
            interface_game.parse_instruction(resp);
            refresh();
        #endif
    }
    
    std::string the_score = std::to_string(game.getScore()); // envoie du score au client une dernier fois
    resClient(send_response_pipe,&the_score);

    #ifdef TEST_GAME
        interface_game.close();
    #endif

    //sauvegarde du score
   save_score(sett_game->pseudo_hote,game.getScore());
   if (sett_game->nb_player == 2){
       save_score(sett_game->pseudo_other,game.getScore());
   }

    std::cout << " score : " << game.getScore() << std::endl;

    // mettre l'etat du jeu pour ce client a false pour qu'il puisse lancer un autre jeu
    mtx_game.lock();
    for(size_t i =0; i < _pipe_running.size(); i++){
        if(strcmp(_pipe_running.at(i)->pid,sett_game->pid)== 0){
            // mettre le jeu a false pour lancer une autre partie
           _pipe_running.at(i)->in_game = false; break; 
        }
    }
    
    mtx_game.unlock();
}

void Server::resClient(char* pipe, std::string* res){
    char to_send[Constante::CHAR_SIZE];
    strcpy(to_send,res->c_str());
    
    #ifdef TEST_GAME
        std::cout << "to affiche : "<< to_send << std::endl;
    #endif
    int fd = open(pipe,O_WRONLY);
    if (fd != -1) write(fd, to_send, Constante::CHAR_SIZE);
    else std::cerr << "[ERROR] settings non ecrit " << std::endl;

    #ifdef DEBUG_GAME
        std::cout << "TO CLIENT : "<<to_send<< std::endl;
    #endif
    close(fd);
}

/**
 * @brief lis le pipe d'input
 * 
 * @param pipe : le pipe à lire 
 * @return int : l'etat de lecture s'il y a eu une erreur ou pas
 */
int Server::read_game_input(char * pipe, int *inp){
    int message[11];
    
    int fd =open(pipe, O_RDONLY); //open pipe
    if (fd != -1){
        int val = read(fd,&message,sizeof(int)*11); 
        if (val == -1)std::cerr << "[ERROR] CAN'T READ IN INPUT 2 PIPE " <<std::endl;
        
    }
    else{ // erreur possible
        std::cerr << "[ERROR PIPE INPUT 2 ]" <<std::endl;
        close(fd);
        return Constante::ERROR_PIPE_GAME;
    };
    close(fd);
    #ifdef DEBUG_GAME
        std::cout <<"FROM CLIENT : [ ";
        for(int i = 0; i <11; i++)
            std::cout  <<message[i]<< ", ";
        std::cout << ']' <<std::endl;
    #endif

    for(int i = 0; i <11; i++) // remplir l'arrays avec les inputes
        inp[i] = message[i];

    return Constante::ALL_GOOD;

}

/**
 * @brief Enregistre le score sur la database
 * 
 * @param pseudo1 
 * @param score 
 */
void Server::save_score(char* pseudo, int score){
    _db.updateScore(score,pseudo);
}

void Server::close_me(int sig){
    for(size_t i=0;i < _pipe_running.size();i++){
        kill(atoi(_pipe_running.at(i)->pid),SIGINT);
    }
    std::cout <<"\n -----------------------|    FERMETURE EN COURS    |-----------------------\n\n " << std::endl;
    sleep(2);
}// handle CTRL + C signal ==> save db
















