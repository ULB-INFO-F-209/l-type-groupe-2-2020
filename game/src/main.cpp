#include <cstdint>
//#include "game.hpp"
#include "CurrentGame.hpp"

int main(int argc, char **argv){

    /*int init_status = init();

    if(init_status == 0)
        run();

    close();*/

    CurrentGame game(false, 80, easy, false);
    game.run();

    return 0;
}
