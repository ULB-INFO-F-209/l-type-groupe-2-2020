#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


char PID_SERVER[100];

void initConnexion(){
    int fd;
    char message[100];
    sprintf(message,"%d",getpid());
    //printf("%s",message);
    
    fd = open("/tmp/connexion",O_WRONLY);
    if (fd != -1){
        write(fd,message,strlen(message)+1);
        printf("Connexion fait \n");

        /**
         * NE PAS TOUCHER SVP
         * 
        char pipe_name[100];
        sprintf(pipe_name,"/tmp/pipefile_%d",getpid());
        close(fd);

        //sleep(2);

        if (int ret_val = mkfifo(pipe_name,0666) > 1 ){ // gestion des erreurs

        std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
        exit(1);
        }
        else{
            std::cout << "creation du pipe : " << pipe_name <<std::endl;
        }




        int fd2 =open(pipe_name, O_RDONLY);
        if (fd2 < 0){
            std::cout << "Error in open pipe_name: " <<pipe_name<<std::endl;
            return;
        }
        
        while(true){
            
                //std::cout << "je suis ici " << std::endl;
                int val = read(fd2,PID_SERVER,100);
                if(val >= 0) {
                    std::cout << "PID du serveur :" <<PID_SERVER<<std::endl;
                    std::cout << "Connexion avec le serverur fait " << std::endl;
                    close(fd2);
                    break;
                
                }

        }*/
            
    }
    else{
        printf("pas de connexion init connexion \n");

    }
    close(fd);


}

void sendInput(){
    int fd;
    char pipe_name[100] = {"/tmp/reponse"};
    //sprintf(pipe_name,"",getpid());
    char message[100];
    sprintf(message,"Ma-Salim-1783-%d",getpid());
    //printf("%s",message);
    
    fd = open(pipe_name,O_WRONLY);
    if (fd != -1){
        write(fd,message,strlen(message)+1);
        printf("Input fait  \n");
    } else{
        printf("pas de send Input\n");
    }
    close(fd);
}

void receiveInput(){
    int fd;
    char message[100];
    char pipe_name[100];
    sprintf(pipe_name,"pipefile_%d",getpid());
    while (true){
        fd =open(pipe_name, O_RDONLY);
        if (fd != -1){
            int val = read(fd,message,100);
            std::cout << "reponse du message  :" <<message<<std::endl;
            close(fd); 
            break;
        }
    }
}

int main(){

    printf("1er msg\n");
    initConnexion();
    sendInput();

    return 0;

}
