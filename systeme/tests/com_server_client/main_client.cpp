#include "Client.hpp"

int main(int argc, char const *argv[])
{
	int a = 0;
	Client zanilia{};
	zanilia.signUp("salu", "123");
	
	for (int i = 0; i < 1000000000; ++i)
	{
		a++;
	}
	/*
	zanilia.addFriend("helin");
	*/
	
	return 0;
}