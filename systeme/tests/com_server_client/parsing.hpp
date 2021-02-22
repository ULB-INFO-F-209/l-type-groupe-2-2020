/*
	ensemble d'opération d'encodage et de decodage!
*/

#ifndef PARSING_HPP
#define PARSING_HPP

#include <cstring>
#include <vector>
#include <iostream>
#include <string>

namespace Parsing{
	struct Profile;
	struct Game_settings;

	//encodage
	void profile_list_to_str(char *buffer,std::vector<Profile*> prof);
	void profile_to_str(char *buffer, Profile *prof);
	void create_game_to_str(char *buffer, Game_settings * settings);

	//decodage
	void profile_list_from_str(char *buffer,std::vector<Profile*> prof);
	void profile_from_str(char *buffer, Profile *prof);
	void create_game_from_str(char *buffer, Game_settings * settings);
	void parsing(char* str, char* token1, char* token2 = nullptr);
}

//Les structures
struct Parsing::Profile
{
	char pseudo[20];
	int score;	
	Profile(char *p, int s){sprintf(pseudo,"%s", p); score=s;}
};

struct Parsing::Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20];
	float drop_rate;
	bool ally_shot=false;
	int nb_lives=5;

};

#endif
