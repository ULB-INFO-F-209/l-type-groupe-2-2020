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
#include "MapHandler.hpp"
#include "Template.hpp"

//enum difficulty{easy, medium, hard};

namespace Parsing{
	using Profile=Profile;
	using Creator=DatabaseLevel;
	using Game_settings=Template::Game_settings;
	using Enemy_template=Template::Enemy_template;
	using Obstacle_template=Template::Obstacle_template;
	using Player=Template::Player_template;
	using Level=Template::Level;
	using difficulty=Template::difficulty;

	//encodage
	void profile_list_to_str(char *buffer,std::vector<Profile> *prof);
	void profile_to_str(char *buffer, Profile prof);
	void create_game_to_str(char *buffer,const Game_settings * settings);
	void profile_list_to_str(char* buffer, std::vector<std::string> *list);
	std::string level_to_str(Level *my_level, const std::string name);
	std::string creator_list_to_str(std::vector<Creator> creator_list);
	std::string creator_to_str(Creator author);

	//decodage
	void profile_list_from_str(char *buffer,std::vector<Profile> *prof);
	void profile_from_str(char *buffer, Profile *prof);
	void create_game_from_str(char *buffer, Game_settings * settings);
	void parsing(char* str, char* token1, char* token2 = nullptr);
	Level level_from_str(std::string);
	std::vector<Creator> creator_list_from_str(std::string);
	Creator creator_from_str(std::string);
}


#endif
