#include "server.hpp"
#include <stdexcept>
#include <thread>
#include <vector>


Server::Server(){

    if (!isServerActive()){ // pas actif
        createPipe("connexion");
        std::cout << "Serveur connecter ... \n";}
        _is_active = true;
        std::thread listening_connexion(initConnexion) // thread d'ecoute (deamon)
    }
    else
        std::cerr << "[ERROR SERVER ALREADY ACTIVE]" << std::endl; exit(1);
    
}

void Server::createPipe(const char *name){

    
    if (int ret_val = mkfifo(name,0666) > 1 ){ // gestion des erreurs

    std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
    exit(1);
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
    
    
    return 0;
}