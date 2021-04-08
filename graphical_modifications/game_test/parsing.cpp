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
void Parsing::create_game_to_str(char *buffer,const Game_settings * settings){
	sprintf(buffer, "%d&%s&%s&%d&%d&%d&%s", 				 settings->nb_player,
										 settings->pseudo_hote,
										 settings->pseudo_other,
										 settings->drop_rate,
										 settings->ally_shot,
										 settings->nb_lives,
										 settings->difficulty_str);
	//buffer -> "nb_player&pseudo_hote&other_pseudo&drop_rate&ally_shot&nb_lives"
}

std::string Parsing::level_to_str(Level *my_level, const std::string name){
	std::string buffer = std::string("LS_") + std::string(name) + "_";

	//player info
	Player p = (my_level->player);
	buffer += std::to_string(p.skin) +"_" + std::to_string(p.skin2) + "_" + std::to_string(p.hp) + "_" + std::to_string(p.damage) + "_" + std::to_string(p.speed);

	//enemy
	buffer += "|";
	for(auto e : my_level->ennemy_list){
		buffer += std::to_string(e.x) + "_" + std::to_string(e.tick) + "_" + std::to_string(e.skin) + "_" ;
		buffer += std::to_string(e.hp) + "_" + std::to_string(e.damage) + "_" + std::to_string(e.bonus) + "_" + std::to_string(e.speed);
		buffer += "&";
	}
	buffer += "|";
	for(auto o : my_level->obs_list){
		buffer += std::to_string(o.x) + "_" + std::to_string(o.tick) + "_" + std::to_string(o.skin) + "_" ;
		buffer += std::to_string(o.hp) + "_" + std::to_string(o.damage) + "_" + std::to_string(o.speed);
		buffer += "&";
	}
	std::cout << "level   = " << buffer<<std::endl;
	return buffer;

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

Parsing::Level Parsing::level_from_str(std::string buffer){
	Level my_level; 
	constexpr char delim_obj = '&';
	constexpr char delim_zone = '|';
	constexpr char delim_attr= '_';

	//player zone
	std::size_t idx = buffer.find(delim_zone);
	std::string player_zone = buffer.substr(0,idx);
	buffer = buffer.substr(idx+1, buffer.size());
	std::cout << "Player = "<< player_zone<<std::endl;

	idx = player_zone.find(delim_attr);
	std::string lettre = player_zone.substr(0,idx); //skin
	player_zone = player_zone.substr(idx+1, player_zone.size());

	idx = player_zone.find(delim_attr);
	std::string name = player_zone.substr(0,idx); //skin
	player_zone = player_zone.substr(idx+1, player_zone.size());

	idx = player_zone.find(delim_attr);
	my_level.player.skin = std::stoi(player_zone.substr(0,idx)); //skin
	player_zone = player_zone.substr(idx+1, player_zone.size());

	idx = player_zone.find(delim_attr);
	my_level.player.skin2 = std::stoi(player_zone.substr(0,idx)); //skin2
	player_zone = player_zone.substr(idx+1, player_zone.size());

	idx = player_zone.find(delim_attr);
	my_level.player.hp = std::stoi(player_zone.substr(0,idx)); //hp
	player_zone = player_zone.substr(idx+1, buffer.size());

	idx = player_zone.find(delim_attr);
	my_level.player.damage = std::stoi(player_zone.substr(0,idx)); //damage
	player_zone = player_zone.substr(idx+1, player_zone.size());

	idx = player_zone.find(delim_attr);
	my_level.player.speed = std::stoi(player_zone.substr(0,idx)); //speed
	player_zone = player_zone.substr(idx+1, player_zone.size());

	//ennemy zone
	idx = buffer.find(delim_zone);
	std::string enemy_zone = buffer.substr(0,idx);
	buffer = buffer.substr(idx+1, buffer.size());
	std::cout << "enemy  = "<< enemy_zone<<std::endl;

	while(enemy_zone.size() > 1){
		Enemy e;

		idx = enemy_zone.find(delim_obj);
		std::string object = enemy_zone.substr(0,idx);
		enemy_zone = enemy_zone.substr(idx+1, enemy_zone.size());
		
		idx = object.find(delim_attr);
		e.x = std::stoi(object.substr(0,idx)); // x pos
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.tick = std::stoi(object.substr(0,idx)); //tick
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.skin = std::stoi(object.substr(0,idx)); //skin
		object = object.substr(idx+1, object.size());


		idx = object.find(delim_attr);
		e.hp = std::stoi(object.substr(0,idx)); //hp
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.damage = std::stoi(object.substr(0,idx)); //damage
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.bonus = std::stoi(object.substr(0,idx)); //speed
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.speed = std::stoi(object.substr(0,idx)); //speed
		object = object.substr(idx+1, object.size());

		my_level.ennemy_list.push_back(e);
	}

	//obstacle Zone
	idx = buffer.find(delim_zone);
	std::string obs_zone = buffer.substr(0,idx);
	buffer = buffer.substr(idx+1, buffer.size());
	std::cout << " obstacle = "<< obs_zone<<std::endl;

	while(obs_zone.size() > 1){
		Obstacle e;

		idx = obs_zone.find(delim_obj);
		std::string object = obs_zone.substr(0,idx);
		obs_zone = obs_zone.substr(idx+1, obs_zone.size());

		idx = object.find(delim_attr);
		e.x = std::stoi(object.substr(0,idx)); //skin2
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.tick = std::stoi(object.substr(0,idx)); //skin2
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.skin = std::stoi(object.substr(0,idx)); //skin
		object = object.substr(idx+1, object.size());


		idx = object.find(delim_attr);
		e.hp = std::stoi(object.substr(0,idx)); //hp
		object = object.substr(idx+1, buffer.size());

		idx = object.find(delim_attr);
		e.damage = std::stoi(object.substr(0,idx)); //damage
		object = object.substr(idx+1, object.size());

		idx = object.find(delim_attr);
		e.speed = std::stoi(object.substr(0,idx)); //speed
		object = object.substr(idx+1, object.size());

		my_level.obs_list.push_back(e);
	}

	return my_level;
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



