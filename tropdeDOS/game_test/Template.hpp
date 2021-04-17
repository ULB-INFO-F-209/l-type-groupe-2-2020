#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP
#include <vector>

namespace Template{
	struct Game_settings;
	struct Enemy_template;
	struct Obstacle_template;
	struct Player_template;
	struct Level;
	enum difficulty{easy, medium, hard};
}
struct Template::Enemy_template{
	int x = 0;
	int y =0 ;
	int tick = 0;
	int skin = 0; // skin 1, skin2, skin3
	int hp = 70;
	int damage=30;
	int bonus = 0;

	void get_values(int *res){
		res[0] = x;
		res[1] = hp;
		res[2] = tick;
		res[3] = damage;
	}
};

struct Template::Obstacle_template{
	int x = 0; 
	int y = 0;
	int tick = 0;
	int skin = 0; //planete, soleil, lune, etoiles
	int hp = 70;
	int damage=30;

	void get_values(int *res){
		res[0] = x;
		res[1] = hp;
		res[2] = tick;
		res[3] = damage;
	}
};

struct Template::Player_template{
	int skin = 0; //planete, soleil, lune, etoiles
	int skin2 = 0;
	int hp = 70;
	int damage=30;
	int speed = 2; //SLUG, TURTLE, HUMAN, HORSE,CHEETAHs
};

struct Template::Level{
	Player_template player{};

	//Enemy session
	std::vector<Enemy_template> enemy_list{};

	//obstacle session
	std::vector<Obstacle_template> obs_list{};
};

struct Template::Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20] = {"Null"};
	int drop_rate=100;
	bool ally_shot=false;
	int nb_lives=1;
	char difficulty_str[20] = "easy";
	difficulty diff{difficulty::easy};
    char pid[10];
};
#endif