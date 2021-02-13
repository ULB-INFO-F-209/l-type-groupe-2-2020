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
void Parsing::leaderboard_from_str(char *buffer,std::vector<Profile*> prof){
	std::string cpp_str_buffer(buffer);
	const char delimiteur_score = '&';
	const char delimiteur_nom = '|';
	Profile * Player_profile=nullptr;

	// TOTEST !!!
	while(std::size_t index = cpp_str_buffer.find(delimiteur_nom) != cpp_str_buffer.npos){ // pas sur pour le npos
		std::string name_and_score = cpp_str_buffer.substr(0,index);
		cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());

		index = name_and_score.find(delimiteur_score);
		Player_profile->pseudo = (name_and_score.substr(0,index)).c_str();
		Player_profile->score = atoi((name_and_score.substr(index+1,name_and_score.size()).c_str()));
		prof.push_back(Player_profile);
	}

}
void Parsing::pseudo_list_from_str(char *buffer, std::vector<char*> list){
	// buffer -> "pseudo1&pseudo2&pseudo3&pseudo4..."
	std::string cpp_str_buffer(buffer);
	const char delimiteur_nom = '&';
	while(std::size_t index = cpp_str_buffer.find(delimiteur_nom) != cpp_str_buffer.npos){
		std::string name = cpp_str_buffer.substr(0,index);
		cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
		list.push_back(name);
	}
	
}
void Parsing::profile_from_str(char *buffer, Profile *prof){
	//

}
void Parsing::create_game_from_str(char *buffer, Game_settings * settings){
	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives"
	std::string cpp_str_buffer(buffer);
	const char delimiteur_score = '&';
	std::size_t index = cpp_str_buffer.find(delimiteur_nom);

	//nb player
	std::string option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives = atoi(option);

	//pseudo_hote
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives =option.c_str();

	//pseudo_other
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives =option.c_str();

	//drop_rate
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives = atoi(option); // TODO drop_rate est un float trouvé un equivalente de atoi pour float

	//ally_shot
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives = atoi(option); //TODO changer le false en un nb 0 ou 1 plus simple pour la convertion

	//nb_lives
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives = atoi(option);

}