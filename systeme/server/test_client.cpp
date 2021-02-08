#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>

void initConnexion(){
    int fd;
    char message[100];
    sprintf(message,"%d",getpid());
    //printf("%s",message);
    
    fd = open("connexion",O_WRONLY);
    if (fd != -1){
        write(fd,message,strlen(message)+1);
        printf("Connexion fait 2 \n");

    }
    else{
        printf("pas de connexion init connexion \n");

    }
    close(fd);

}


void sendInput(){

    int fd;
    char pipe_name[100];
    sprintf(pipe_name,"pipefile_%d",getpid());
    char message[100];
    sprintf(message,"Ma-Vinove-123-%d",getpid());
    //printf("%s",message);
    
    fd = open(pipe_name,O_WRONLY);
    if (fd != -1){
        write(fd,message,strlen(message)+1);
        printf("Input fait 2 \n");

    }
    else{
        printf("pas de connexion send Input\n");

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
    printf("COnnexion fait\n");
    sendInput();
    printf("Input fait\n");

    return 0;

}