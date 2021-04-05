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

