#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();

	//db.createAccount("helin", "123");
	//db.createAccount("aissa", "blabla");
	//db.createAccount("Vin", "toto");
	//db.createAccount("poubelle", "mdp");


	std::cout << "db.find(\"Vin\") : " << db.find("Vin") << std::endl;
    std::cout << "db.find(\"haha\") : " << db.find("haha") << std::endl;

    std::cout << "db.verifyLogin(\"aissa\", \"blabla\") : " << db.verifyLogin("aissa", "blabla") << std::endl;


	db.dbSave();
	return 0;
}