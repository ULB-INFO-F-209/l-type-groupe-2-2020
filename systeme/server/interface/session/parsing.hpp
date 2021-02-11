/*
	Une sorte d'interface à la java
	ne represente pas un objet 
	mais un ensemble d'opération d'encodage et de decoddage!
*/

#ifndef PARSING_HPP
#define PARSING_HPP

#include <vector>
#include <iostream>

struct Profile
{
	char pseudo[20];
	int score;	
};

struct Game_settings
{
	
};

class Parsing 
{
public:
	Parsing()=default;

	//encodage
	void leader_board_to_str(char *buffer,std::vector<Profile*> prof);
	void pseudo_list_to_str(char *buffer, std::vector<char*> list); //same for friend request
	void profil_to_str(char *buffer, Profile *prof);
	void create_game_to_str(char *buffer, Game_settings * settings);

	//decodage
	void leaderboard_from_str(char *buffer,std::vector<Profile*> prof);
	void pseudo_list_from_str(char *buffer, std::vector<char*> list);
	void profile_from_str(char *buffer, Profile *prof);
	void create_game_from_str(char *buffer, Game_settings * settings);


	~Parsing()=default;
	
};
#endif