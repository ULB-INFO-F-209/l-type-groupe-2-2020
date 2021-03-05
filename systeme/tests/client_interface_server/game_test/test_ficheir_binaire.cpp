
#include "Player.hpp"
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <sys/stat.h>

struct to_bin{
    Player p1[2];
};

void write_for_me(){
    to_bin to_send{Player(10),Player(8)};

    FILE *f;
    char c_path[] = "fichier";
    
    struct stat buffer;

    if (!(stat (c_path, &buffer) == 0)){
        std::cout << "je suis la" << std::endl;
    	f = fopen(c_path, "wb");
    	if (f == nullptr){
            throw "Could not create file!";
            fclose(f);
            exit(1);
        }
        else{
            fwrite(&to_send,sizeof(to_bin),1,f);
            std::cout << "ecriture OK !"<<std::endl;
        }
    } 
    fclose(f);
    
};

void read_for_me(){
    to_bin to_read;

    FILE *f;
    fopen("fichier.bin","rb");
    if (f==nullptr){
        std::cout << "y a un pb 2"<<std::endl;
        exit(1);
    }
    else{
        fread(&to_read,sizeof(to_bin),1,f);
        std::cout << "lecutre OK !"<<std::endl;
    }
    fclose(f);
};

int main(){

    
    write_for_me();
    sleep(10);
    // --------------------------------------------------------------
    read_for_me();

    return 0;
}