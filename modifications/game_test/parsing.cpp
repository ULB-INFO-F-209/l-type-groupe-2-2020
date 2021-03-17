 	/*
		!!! pas oublier de gérer les erreurs ect!!!
	*/
#include "parsing.hpp"

//encodage
void Parsing::profile_list_to_str(char *buffer, std::vector<Profile>* list){
    size_t size = list->size();
    std::string buff;
    for (size_t i = 0; i < size; ++i){
        std::string tmp = list->at(i).pseudo;
        buff.append(tmp);
        buff.push_back('|');
        std::string tmp2 = std::to_string(list->at(i).score);
        buff.append(tmp2);
        buff.push_back('&');
    }
    strcpy(buffer,buff.c_str());

	// buffer -> "pseudo1|score&pseudo2|score&pseudo3|score..." 
}
void Parsing::profile_to_str(char *buffer, Profile prof){
	sprintf(buffer, "%s&%d", prof.pseudo, prof.score);
	//buffer -> "pseudo&score" 
}
void Parsing::create_game_to_str(char *buffer, Game_settings * settings){
	sprintf(buffer, "%d&%s&%s&%d&%d&%d&%s", 				 settings->nb_player,
										 settings->pseudo_hote,
										 settings->pseudo_other,
										 settings->drop_rate,
										 settings->ally_shot,
										 settings->nb_lives,
										 settings->difficulty_str);
	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives"
}

//decodage
void Parsing::profile_list_from_str(char *buffer,std::vector<Profile> *prof){
	std::string cpp_str_buffer(buffer);
	constexpr char delimiteur_score = '&';
	constexpr char delimiteur_nom = '|';

	// TO  TEST !!! : merci
	while(cpp_str_buffer.size() > 1){ // pas sur pour le npos
		std::size_t index = cpp_str_buffer.find(delimiteur_score);
		std::string name_and_score = cpp_str_buffer.substr(0,index);
		cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
		
		
		size_t idx = name_and_score.find(delimiteur_nom);
		Profile Player_profile{name_and_score.substr(0,idx).c_str(), atoi((name_and_score.substr(idx+1,name_and_score.size()).c_str()))};
		/*strcpy(Player_profile.pseudo, (name_and_score.substr(0,idx)).c_str());
		std::cout << "name_scor "<<Player_profile.pseudo<<std::endl;
		Player_profile.score = atoi((name_and_score.substr(idx+1,name_and_score.size()).c_str()));
		std::cout << "name_scor "<<Player_profile.score<<std::endl;*/
		prof->push_back(Player_profile);
	}

}

void Parsing::profile_from_str(char *buffer, Profile *prof){

	std::string cpp_str_buffer(buffer);
	constexpr char delimiteur_nom = '&';
	size_t idx = cpp_str_buffer.find(delimiteur_nom);
	strcpy(prof->pseudo, cpp_str_buffer.substr(0,idx).c_str());
	prof->score = atoi((cpp_str_buffer.substr(idx+1,cpp_str_buffer.size()).c_str()));
}

void Parsing::create_game_from_str(char *buffer, Game_settings * settings){
	//buffer -> "P&nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives&difficulty&pid"
	// P&1&vinove44&Null&100&0&1&easy&723

	std::string cpp_str_buffer(buffer);
	const char delimiteur_score = '&';

	std::size_t index = cpp_str_buffer.find(delimiteur_score);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.length());
	index = cpp_str_buffer.find(delimiteur_score);
	//1&vinove44&Null&100&0&1&easy&723

	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives&difficulty&pid""

	//nb player
	std::string option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	settings->nb_player = atoi(option.c_str());
	//option = option.substr(index, option.length());

	//vinove44&Null&100&0&1&easy&723
	//buffer -> "pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives&difficulty&pid""
	//pseudo_hote
	index = cpp_str_buffer.find(delimiteur_score);
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	strcpy(settings->pseudo_hote, option.c_str());

	//Null&100&0&1&easy&723
	//buffer -> "other_pseudo&drop_rate&ally_shot&nb_lives&difficulty&pid""
	//pseudo_other
	index = cpp_str_buffer.find(delimiteur_score);
	//option = cpp_str_buffer.substr(index, cpp_str_buffer.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	strcpy(settings->pseudo_other, option.c_str());

	//100&0&1&easy&723
	//buffer -> "drop_rate&ally_shot&nb_lives&difficulty&pid""
	//drop_rate
	index = cpp_str_buffer.find(delimiteur_score);
	//option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	settings->drop_rate = atoi(option.c_str()); // TODO drop_rate est un float trouvé un equivalente de atoi pour float

	// 0&1&easy&723
	//buffer -> "ally_shot&nb_lives&difficulty&pid""
	//ally_shot
	index = cpp_str_buffer.find(delimiteur_score);
	//option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	settings->ally_shot = atoi(option.c_str()); //TODO changer le false en un nb 0 ou 1 plus simple pour la convertion

	// 1&easy&723
	//buffer -> "nb_lives&difficulty&pid""
	//nb_lives
	index = cpp_str_buffer.find(delimiteur_score);
	//option = option.substr(index, option.length());
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	settings->nb_lives = atoi(option.c_str());
	
	//easy&723
	//buffer -> "difficulty&pid""
	//difficulty
	index = cpp_str_buffer.find(delimiteur_score);
	option = cpp_str_buffer.substr(0,index);
	cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());
	settings->diff = !strcmp(option.c_str(), "easy")? easy: !strcmp(option.c_str(), "medium")? medium: hard;
	
	//pid
	strcpy(settings->pid,cpp_str_buffer.c_str());
	//cpp_str_buffer = cpp_str_buffer.substr(index+1,cpp_str_buffer.size());

	


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



