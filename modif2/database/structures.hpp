#include "account.hpp"

struct Profile{
	char pseudo[20];
	int score;
	Profile()=default;
	Profile(const char *p, int s){sprintf(pseudo,"%s", p); score=s;}
	Profile(Account acc){acc.getPseudo(pseudo); score = acc.getScore();}
};


struct Enemy{
	int x = 0;
	int tick = 0;
	int skin = 0; // skin 1, skin2, skin3
	int hp = 70;
	int damage=30;
	int bonus = 0;
	int speed = 2; //SLUG, TURTLE, HUMAN, HORSE,CHEETAH

	void get_values(int *res){
		res[0] = x;
		res[1] = hp;
		res[2] = tick;
		res[3] = damage;
	}
};

struct Obstacle{
	int x = 0; 
	int tick = 0;
	int skin = 0; //planete, soleil, lune, etoiles
	int hp = 70;
	int damage=30;
	int speed = 2; //SLUG, TURTLE, HUMAN, HORSE,CHEETAH
	

	void get_values(int *res){
		res[0] = x;
		res[1] = hp;
		res[2] = tick;
		res[3] = damage;
	}
};

struct Player{
	int skin = 0; //planete, soleil, lune, etoiles
	int hp = 70;
	int damage=30;
	int speed = 2; //SLUG, TURTLE, HUMAN, HORSE,CHEETAH
};

struct Level{
	Player player1;
	Player player2;

	//Enemy session
	std::vector<Enemy> ennemy_list{};

	//obstacle session
	std::vector<Obstacle> obs_list{};

};