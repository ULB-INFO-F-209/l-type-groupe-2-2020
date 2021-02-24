	/*
		!!! pas oublier de gérer les erreurs ect!!!
	*/
#include "parsing.hpp"

//encodage
void Parsing::profile_list_to_str(char *buffer, std::vector<Profile*>* list){
	size_t size = list->size();
	for (size_t i = 0; i < size; ++i){
		sprintf(buffer, "%s|%d&", list->at(i)->pseudo,list->at(i)->score);
	}
	// buffer -> "pseudo1|score&pseudo2|score&pseudo3|score..." 
}
void Parsing::profile_to_str(char *buffer, Profile *prof){
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
void Parsing::profile_list_to_str(char* buffer, std::vector<char*> *list){
	size_t size = list->size();
	for (size_t i = 0; i < size; ++i){
		sprintf(buffer, "%s&", list->at(i));
	}
}

//decodage
void Parsing::profile_list_from_str(char *buffer,std::vector<Profile*> prof){
	std::string cpp_str_buffer(buffer);
	const char delimiteur_score = '&';
	const char delimiteur_nom = '|';
	Profile * Player_profile=nullptr;

	// TO  TEST !!!
	while(std::size_t index = cpp_str_buffer.find(delimiteur_nom) != cpp_str_buffer.empty()){ // pas sur pour le npos
		std::string name_and_score = cpp_str_buffer.substr(0,index);
		cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());

		index = name_and_score.find(delimiteur_score);
		strcpy(Player_profile->pseudo, (name_and_score.substr(0,index)).c_str());
		Player_profile->score = atoi((name_and_score.substr(index+1,name_and_score.size()).c_str()));
		prof.push_back(Player_profile);
	}

}

void Parsing::profile_from_str(char *buffer, Profile *prof){
	//

}
void Parsing::create_game_from_str(char *buffer, Game_settings * settings){
	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives"
	std::string cpp_str_buffer(buffer);
	const char delimiteur_score = '&';
	std::size_t index = cpp_str_buffer.find(delimiteur_score);

	//nb player
	std::string option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_player = atoi(option.c_str());
	option = option.substr(index, option.length());

	//pseudo_hote
	index = cpp_str_buffer.find(delimiteur_score);
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	strcpy(settings->pseudo_hote, option.c_str());

	//pseudo_other
	index = cpp_str_buffer.find(delimiteur_score);
	option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	strcpy(settings->pseudo_other, option.c_str());

	//drop_rate
	index = cpp_str_buffer.find(delimiteur_score);
	option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->drop_rate = std::atof(option.c_str()); // TODO drop_rate est un float trouvé un equivalente de atoi pour float

	//ally_shot
	index = cpp_str_buffer.find(delimiteur_score);
	option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->ally_shot = atoi(option.c_str()); //TODO changer le false en un nb 0 ou 1 plus simple pour la convertion

	//nb_lives
	index = cpp_str_buffer.find(delimiteur_score);
	option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index,cpp_str_buffer.size());
	settings->nb_lives = atoi(option.c_str());

}
///parsing to withdraw the user's info
void Parsing::parsing(char* str, char* token1, char* token2) {

	std::string token(str);
	token.push_back('&');
	const char del = '&';
	std::size_t index = 0;
	std::string var;
	int i = 0;
	
	while(!token.empty()) {
		index = token.find(del);
		var = token.substr(0, index);
		token = token.erase(0, index+1);
		if (i == 1) { strcpy(token1, var.c_str()); }
		else if (i == 2 && token2) { strcpy(token2, var.c_str()); }
		i++;
	}
}