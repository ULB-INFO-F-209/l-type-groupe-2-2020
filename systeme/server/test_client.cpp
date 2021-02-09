#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <signal.h>


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


        char pipe_name[100];
        sprintf(pipe_name,"/tmp/pipefile_%d",getpid());
        while(true){
            fd =open(pipe_name, O_RDONLY);
            if (fd != -1){
                //std::cout << "je suis ici " << std::endl;
                int val = read(fd,PID_SERVER,100);
                std::cout << "PID du serveur :" <<PID_SERVER<<std::endl;
                break;
                
                
            }
            else{
                std::cout << "Pas recu le pid serveur :" <<PID_SERVER<<std::endl;
            }
            close(fd);
        }

    }
    else{
        printf("pas de connexion init connexion \n");

    }
    close(fd);

    
    
    

}


void sendInput(){

    int fd;
    char pipe_name[100];
    sprintf(pipe_name,"/tmp/pipefile_%d",getpid());
    char message[100];
    sprintf(message,"Ma-Salim-123-%d",getpid());
    //printf("%s",message);
    
    fd = open(pipe_name,O_WRONLY);
    if (fd != -1){
        while(write(fd,message,strlen(message)+1)){printf("Pas encore envoyer \n");kill(atoi(PID_SERVER),SIGUSR1);};
        printf("Input fait  \n");

    }
    else{
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