#include <iostream>

#include "server.hpp"

int main(int argc, char const *argv[])
{
	Server my_server = Server();
	my_server.start();
	return 0;
}