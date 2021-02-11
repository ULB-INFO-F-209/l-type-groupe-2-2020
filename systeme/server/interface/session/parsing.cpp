	/*
		!!! pas oublier de gérer les erreurs ect!!!
	*/
#include "parsing.hpp"

//encodage
void Parsing::leader_board_to_str(char *buffer,std::vector<Profile*> prof){
	size_t size = prof.size();
	for (size_t i = 0; i < size; ++i){
		sprintf(buffer, "%s&%d|", prof[i]->pseudo, prof[i]->score);
	}
	//buffer -> pseudo1&score|pseudo2&score|pseudo3&score|
}
void Parsing::pseudo_list_to_str(char *buffer, std::vector<char*> list){
	size_t size = list.size();
	for (size_t i = 0; i < size; ++i){
		sprintf(buffer, "%s&", list[i]);
	}
	// buffer -> "pseudo1&pseudo2&pseudo3&pseudo4..." 
}
void Parsing::profil_to_str(char *buffer, Profile *prof){
	sprintf(buffer, "%s&%d", prof->pseudo, prof->score);
	//buffer -> "pseudo&score" 
}
void Parsing::create_game_to_str(char *buffer, Game_settings * settings){
	sprintf(buffer, "%d&%s&%s&%f&%d&%d", settings->nb_player,
										 settings->pseudo_hote,
										 settings->pseudo_other,
										 settings->drop_rate,
										 settings->ally_shot,
										 settings->nb_lives);
	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives"
}

//decodage
void Parsing::leaderboard_from_str(char *buffer,std::vector<Profile*> prof){}
void Parsing::pseudo_list_from_str(char *buffer, std::vector<char*> list){}
void Parsing::profile_from_str(char *buffer, Profile *prof){}
void Parsing::create_game_from_str(char *buffer, Game_settings * settings){}