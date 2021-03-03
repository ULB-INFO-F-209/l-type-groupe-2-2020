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
	using Profile = Profile;
	struct Game_settings;

	//encodage
	void profile_list_to_str(char *buffer,std::vector<Profile> *prof);
	void profile_to_str(char *buffer, Profile prof);
	void create_game_to_str(char *buffer, Game_settings * settings);
	void profile_list_to_str(char* buffer, std::vector<std::string> *list);

	//decodage
	void profile_list_from_str(char *buffer,std::vector<Profile> *prof);
	void profile_from_str(char *buffer, Profile *prof);
	void create_game_from_str(char *buffer, Game_settings * settings);
	void parsing(char* str, char* token1, char* token2 = nullptr);
}

struct Parsing::Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20];
	int drop_rate=25;
	bool ally_shot=false;
	int nb_lives=3;
	char difficulty_str[20] = "easy";
	difficulty diff;

};

#endif
