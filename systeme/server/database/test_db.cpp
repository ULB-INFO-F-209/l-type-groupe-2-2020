#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();

	db.createAccount("helin", "123");
	db.createAccount("aissa", "blabla");
	//db.createAccount("Vin", "toto");
	//db.createAccount("poubelle", "mdp");

	std::cout << "db.find(\"Vin\") : " << db.find("Vin") << std::endl;
    std::cout << "db.find(\"haha\") : " << db.find("haha") << std::endl;

    std::cout << "db.verifyLogin(\"aissa\", \"blabla\") : " << db.verifyLogin("aissa", "blabla") << std::endl;
    std::cout << "db.addFriend(\"helin\", \"aissa\") : " << db.addFriend("helin", "aissa") << std::endl;

    //std::cout << "db.areFriends(\"helin\", \"aissa\") : " << db.areFriends("helin", "aissa") << std::endl;


	db.dbSave();
	return 0;
}