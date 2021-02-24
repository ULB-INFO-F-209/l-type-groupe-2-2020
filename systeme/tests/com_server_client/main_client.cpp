#include "Client.hpp"

int main()
{
	int a = 0;
	Client zanilia{};
	char res[Constante::CHAR_SIZE];
	Client Django{}, Imene{};

	Imene.signUp("Imene", "caca");
	std::cout << "signUp finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Imene.get_profile(res);
	std::cout << "Profile finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.signUp("salu", "123");
	std::cout << "signUp finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	
	Django.signUp("Django", "123");
	std::cout << "signUp finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.signIn("salu", "123");
	std::cout << "signIn finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.sendFriendRequest("Django");
	std::cout << "Send Friend Request finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Imene.sendFriendRequest("Django");
	std::cout << "Send Friend Request finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.getFriendRequest(res);
	std::cout << "get friend Request finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.addFriend("salu");
	std::cout << "Add friend finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.delFriendRequest("Imene");
	std::cout << "Del friend Requeste finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	zanilia.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Imene.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.delFriend("salu");
	std::cout << "Del friend  finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.delFriend("Django");
	std::cout << "Del friend finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.getFriendList(res);
	std::cout << "GetFriend List finis" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	/*
	zanilia.addFriend("helin");
	*/
	
	return 0;
}