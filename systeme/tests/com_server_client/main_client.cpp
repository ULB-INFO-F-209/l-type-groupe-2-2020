#include "Client.hpp"

int main()
{
	int a = 0;
	Client zanilia{};
	zanilia.signUp("salu", "123");
	std::cout << "signUp finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	Client Django{};
	Django.signUp("Django", "123");
	std::cout << "signUp finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	zanilia.signIn("salu", "123");
	std::cout << "signIn finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	zanilia.addFriend("Django");
	std::cout << "Add friend finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	char res[Constante::CHAR_SIZE];
	zanilia.getFriendRequest(res);
	std::cout << "GetFirendRequest finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	/*
	zanilia.addFriend("helin");
	*/
	
	return 0;
}