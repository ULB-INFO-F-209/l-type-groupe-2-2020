

#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include "Constante.hpp"


typedef struct{
    char mot1[100];
    char mot2[100];
    int age;
} mystruct;

int main(){

    
    if (int ret_val = mkfifo("pipe_test",Constante::PIPE_MODE) > 1 ){ //cree le pipe

        std::cerr << "[ERROR PIPE ("<< ret_val <<")] " << std::endl;
        exit(1);
    }
    else{
        std::cout << "creation du pipe " <<std::endl;
    }


    int fd;
    mystruct message;
    while (true){
        
        fd =open("pipe_test", O_RDONLY);
        if (fd != -1){
            std::cout << std::endl;
            int val = read(fd,&message,sizeof(mystruct)); // TODO verification de val 
            std::cout << "obj :" <<message.mot1<<std::endl;
            std::cout <<message.mot2<<std::endl;
            std::cout <<message.age<<std::endl;

            close(fd);
            
        }
        else{
            std::cerr << "[ERROR PIPE CONNEXION]" <<std::endl;
        }
    }
}