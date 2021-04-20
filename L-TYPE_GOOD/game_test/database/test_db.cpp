#include <iostream>
#include "database.hpp"

int main()
{
	Database db;
	db.dbLoad();

    //std::cout << "db.areFriends(\"helin\", \"aissa\") : " << db.areFriends("helin", "aissa") << std::endl;

	db.createAccount("helin", "123");
	db.createAccount("aissa", "blabla");
	db.createAccount("Vin", "toto");
	db.createAccount("poubelle", "mdp");

	/*
	std::cout << "db.find(\"Vin\") : " << db.find("Vin") << std::endl;
    std::cout << "db.find(\"haha\") : " << db.find("haha") << std::endl;

    std::cout << "db.verifyLogin(\"aissa\", \"blabla\") : " << db.verifyLogin("aissa", "blabla") << std::endl;
    std::cout << "db.verifyLogin(\"aissa\", \"aaa\") : " << db.verifyLogin("aissa", "aaa") << std::endl;
*/

    std::cout << "db.friendRequest(\"Vin\", \"poubelle\") : " << db.friendRequest("Vin", "poubelle") << std::endl;
    std::cout << "db.friendRequest(\"Vin\", \"poubelle\") : " << db.friendRequest("Vin", "poubelle") << std::endl;
    db.display();
    std::cout << "db.addFriend(\"poubelle\", \"Vin\") : " << db.addFriend("poubelle", "Vin") << std::endl;


/*
    std::cout << "db.friendRequest(\"Vin\", \"helin\") : " << db.friendRequest("Vin", "helin") << std::endl;
    std::cout << "db.friendRequest(\"aissa\", \"helin\") : " << db.friendRequest("aissa", "helin") << std::endl;

    std::cout << "db.addFriend(\"helin\", \"aissa\") : " << db.addFriend("helin", "aissa") << std::endl;
    std::cout << "db.addFriend(\"helin\", \"Vin\") : " << db.addFriend("helin", "Vin") << std::endl;
       

    std::cout << "db.addFriend(\"helin\", \"poubelle\") : " << db.addFriend("helin", "poubelle") << std::endl;

    db.removeFriend("Vin", "helin");
    //std::cout << "db.removeFriend(\"Vin\", \"helin\") : " << std::endl;
*/

	db.updateScore(666, "helin");
	db.updateScore(45, "aissa");
	db.updateScore(3, "Vin");

	std::vector<Profile> leaderboard = db.checkLeaderboard();
    db.updateScore(47, "poubelle");
    leaderboard = db.checkLeaderboard();
    std::vector<std::string> levels = db.checkLevels();

/*
    std::vector<char*> amis = db.getFriendList("helin");
    for (auto x : amis)
        std::cout << "amis de helin" << " -> " << x << " : " << strlen(x) << std::endl;
    std::cout << "-----------------" << std::endl;

    amis = db.getFriendList("aissa");
    for (auto x : amis)
        std::cout << "amis de aissa" << " -> " << x << " : " << strlen(x) << std::endl;
    std::cout << "-----------------" << std::endl;

    std::vector<char*> req = db.getFriendRequest("poubelle");
    for (auto y : req)
        std::cout << "requetes de poubelle" << " -> " << y << " : " << strlen(y) << std::endl;
    std::cout << "-----------------" << std::endl;

    Profile hel = db.getProfile("helin");
    std::cout << hel.pseudo << " " << hel.score << std::endl;
    */

	db.dbSave();
	return 0;
}