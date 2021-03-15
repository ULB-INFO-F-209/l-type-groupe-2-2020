
#include "DisplayGame.hpp"

void DisplayGame::parse_instruction(char *buffer){  // A_B_type_x_y&E_H2_valeur&...
	std::string chaine_instruction(buffer);

	while(chaine_instruction.size() > 1){ 
		std::size_t idx = chaine_instruction.find(delimiteur_instruction);  //idx du premier delimiteur_instruction (&)
		std::string instruction = chaine_instruction.substr(0,idx);     	// on retire une instruction
		chaine_instruction = chaine_instruction.substr(idx+1,chaine_instruction.size()); // on garde la chaine sans l instruction
		size_t idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
		std::string type_instruction = instruction.substr(0,idx); 		//on recupère le premier param de l instruction
		instruction = chaine_instruction.substr(idx+1,instruction.size()); //on met à jour l'instruction

		if (type_instruction == "A") 		//Affichage (utiliser des thread?)
			parse_affichage(instruction)
		else if (type_instruction == "E")	//Etat
			parse_etat(instruction)

	}
}


void DisplayGame::parse_affichage(std::string instruction){
	std::string objet; size_t idx 
	int x, y;
	idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
	objet = instruction.substr(0,idx); 		//on recupère le premier param de l instruction
	instruction = instruction.substr(idx+1,instruction.size()); //nettoie instruction
	idx = instruction.find(delimiteur_parametre);
	x = std::stoi(instruction.substr(0,idx)); 		//on recupère le premier param de l instruction
	instruction = instruction.substr(idx+1,instruction.size());
	idx = instruction.find(delimiteur_parametre);
	y = std::stoi(instruction.substr(0,idx));
	instruction = instruction.substr(idx+1,instruction.size()); 

	//dans l'ordre de reccurence (pour eviter trop de comparaison)
	if(objet=="PE") 			//projectile ennemie
		drawProjectile(x,y)
	else if(objet=="PJ")		//projectile joueur
		drawProjectile(x,y,false)
	else if(objet=="E")			//Vaisseau ennemie
		drawEnemy(x,y)
	else if(objet=="1") 		//Vaisseau joueur 1
		drawPlayer(1,x,y)
	else if(objet=="2")			//Vaisseau joueur 2
		drawPlayer(2,x,y)
	else if(objet=="O")			//obstacle
		drawObstacle(x,y)
	else if(objet=="EB") 		//Boss
		drawBoss(x,y)
	else if(objet=="B"){		//Bonus
		idx = instruction.find(delimiteur_parametre);
		int type = std::stoi(instruction.substr(0,idx));  
		drawBonus(type,x,y)
	}
}
void DisplayGame::parse_etat(std::string instruction){
	size_t idx 
	int joueur,hp, vie, score;
	idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
	joueur = instruction.substr(0,idx); 		//on recupère le premier param de l instruction
	instruction = instruction.substr(idx+1,instruction.size()); //nettoie instruction
	idx = instruction.find(delimiteur_parametre);
	hp = std::stoi(instruction.substr(0,idx)); 		
	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);
	vie = std::stoi(instruction.substr(0,idx)); 	
	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);	
	score = std::stoi(instruction.substr(0,idx)); 
	drawEtat(player,hp, score, vie);
}