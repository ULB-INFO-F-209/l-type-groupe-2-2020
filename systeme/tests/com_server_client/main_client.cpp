#include "Client.hpp"

void test1();

int main()
{
	test1();
	//Client Django{}, Imene{},zanilia{};;
	
	return 0;
}

void test1(){
	int a = 0;
	Client zanilia{};
	char res[Constante::CHAR_SIZE];
    char res2[Constante::CHAR_SIZE];
	Client Django{}, Imene{};

    Imene.signUp("Imene", "caca");
    std::cout << "signUp fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    zanilia.signUp("salu", "123");
    std::cout << "signUp fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Django.signUp("Django", "123");
    std::cout << "signUp fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Imene.signIn("Imene", "caca");
    std::cout << "signIn fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    zanilia.signIn("salu", "123");
    std::cout << "signIn fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    Django.signIn("Django", "123");
    std::cout << "signIn fini" << std::endl<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Imene.get_profile(res);
	std::cout << "Profile fini" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	zanilia.sendFriendRequest("Django");
	std::cout << "Send Friend Request fini" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Imene.sendFriendRequest("Django");
	std::cout << "Send Friend Request fini" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.getFriendRequest(res);
	std::cout << "get friend Request fini" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.addFriend("salu");
	std::cout << "Add friend fini" << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	Django.checkLeaderboard(res2);
    std::cout << "Check leaderboard fini" << std::endl<<std::endl;
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
}