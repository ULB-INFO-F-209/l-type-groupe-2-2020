#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();

	//db.create_account(11, "helin", "123");
	//db.create_account(17, "aissa", "blabla");
	//db.create_account(17, "Vin", "toto");
	//db.create_account(7, "poubelle", "mdp");


	std::cout << "db.find(\"Vin\") : " << db.find("Vin") << std::endl;
    std::cout << "db.find(\"haha\") : " << db.find("haha") << std::endl;

    std::cout << "db.verify_login(\"aissa\", \"blabla\") : " << db.verify_login("aissa", "blabla") << std::endl;

	db.dbSave();
	//db.dbLoad();
	return 0;
}