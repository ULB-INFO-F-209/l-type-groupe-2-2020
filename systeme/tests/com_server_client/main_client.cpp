#include "Client.hpp"

int main(int argc, char const *argv[])
{
	Client zanilia{};
	zanilia.signUp("salu", "123");
	sleep(5);
	zanilia.addFriend("helin");
	
	return 0;
}