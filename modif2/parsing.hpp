/*
	ensemble d'opération d'encodage et de decodage!
*/

#ifndef PARSING_HPP
#define PARSING_HPP

#include <cstring>
#include <vector>
#include <iostream>
#include <string>
#include <unistd.h>
#include "database/database.hpp"

enum difficulty{easy, medium, hard};

namespace Parsing{
	using Profile=Profile;
	struct Game_settings;
	struct Enemy;
	struct Obstacle;
	struct Player;
	struct Level;

	//encodage
	void profile_list_to_str(char *buffer,std::vector<Profile> *prof);
	void profile_to_str(char *buffer, Profile prof);
	void create_game_to_str(char *buffer, Game_settings * settings);
	void profile_list_to_str(char* buffer, std::vector<std::string> *list);
	std::string level_to_str(Level *my_level, const std::string name);

	//decodage
	void profile_list_from_str(char *buffer,std::vector<Profile> *prof);
	void profile_from_str(char *buffer, Profile *prof);
	void create_game_from_str(char *buffer, Game_settings * settings);
	void parsing(char* str, char* token1, char* token2 = nullptr);
	Level level_from_str(std::string);
}


struct Parsing::Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20] = {"Null"};
	int drop_rate=100;
	bool ally_shot=false;
	int nb_lives=1;
	char difficulty_str[20] = "easy";
	difficulty diff{easy};
    char pid[10];

};
struct Parsing::Enemy{
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

struct Parsing::Obstacle{
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

struct Parsing::Player{
	int skin = 0; //planete, soleil, lune, etoiles
	int skin2 = 0;
	int hp = 70;
	int damage=30;
	int speed = 2; //SLUG, TURTLE, HUMAN, HORSE,CHEETAHs
};

struct Parsing::Level{
	Player player;

	//Enemy session
	std::vector<Enemy> ennemy_list{};

	//obstacle session
	std::vector<Obstacle> obs_list{};

};
#endif
