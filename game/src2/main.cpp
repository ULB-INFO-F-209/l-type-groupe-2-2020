#include <cstdint>
//#include "game.hpp"
#include "CurrentGame.hpp"

int main(int argc, char **argv){

    /*int init_status = init();

    if(init_status == 0)
        run();

    close();*/

    CurrentGame game;
    game.run();

    return 0;
}
