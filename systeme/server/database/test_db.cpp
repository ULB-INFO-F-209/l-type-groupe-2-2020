#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();

    //std::cout << "db.areFriends(\"helin\", \"aissa\") : " << db.areFriends("helin", "aissa") << std::endl;

	//db.createAccount("helin", "123");
	//db.createAccount("aissa", "blabla");
	//db.createAccount("Vin", "toto");
	//db.createAccount("poubelle", "mdp");

	std::cout << "db.find(\"Vin\") : " << db.find("Vin") << std::endl;
    std::cout << "db.find(\"haha\") : " << db.find("haha") << std::endl;

    std::cout << "db.verifyLogin(\"aissa\", \"blabla\") : " << db.verifyLogin("aissa", "blabla") << std::endl;
    std::cout << "db.verifyLogin(\"aissa\", \"aaa\") : " << db.verifyLogin("aissa", "aaa") << std::endl;

    std::cout << "db.addFriend(\"helin\", \"aissa\") : " << db.addFriend("helin", "aissa") << std::endl;

    std::cout << "db.friendRequest(\"Vin\", \"poubelle\") : " << db.friendRequest("Vin", "poubelle") << std::endl;
    std::cout << "db.friendRequest(\"Vin\", \"poubelle\") : " << db.friendRequest("Vin", "poubelle") << std::endl;
    std::cout << "db.friendRequest(\"aissa\", \"helin\") : " << db.friendRequest("aissa", "helin") << std::endl;

    std::cout << "db.removeFriend(\"aissa\", \"helin\") : " << db.removeFriend("aissa", "helin") << std::endl;

	db.dbSave();
	return 0;
}