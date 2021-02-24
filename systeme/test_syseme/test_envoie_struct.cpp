

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


typedef struct{
    char mot1[100];
    char mot2[100];
    int age;
} mystruct;

int main(){

    mystruct message = {"Django","Caligula",2021};
    int fd;
    fd = open("pipe_test",O_WRONLY);
    if (fd != -1){
        write(fd,&message,sizeof(message));
        printf("ecriture fait \n");
    }
    else{
        printf("pas d'ecriture \n");

    }
    close(fd);
}