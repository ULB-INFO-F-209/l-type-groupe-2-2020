
#include <stdlib.h>
#include <stdio.h>

#include "Menu.hpp"



int main(void) {
	ConnexionMenu cm;
	MainMenu mm;
	FriendMenu fm;

	std::cout <<cm;
	cm.get_user_choice();

    return EXIT_SUCCESS;
}