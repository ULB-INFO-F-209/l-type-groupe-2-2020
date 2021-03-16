
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
			parse_affichage(instruction);
		else if (type_instruction == "E")	//Etat
			parse_etat(instruction);

	}
}


void DisplayGame::parse_affichage(std::string instruction){
	std::string objet; size_t idx ;
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
		drawProjectile(x,y);
	else if(objet=="PJ")		//projectile joueur
		drawProjectile(x,y,false);
	else if(objet=="E")			//Vaisseau ennemie
		drawEnemy(x,y);
	else if(objet=="1") 		//Vaisseau joueur 1
		drawPlayer(1,x,y);
	else if(objet=="2")			//Vaisseau joueur 2
		drawPlayer(2,x,y);
	else if(objet=="O")			//obstacle
		drawObstacle(x,y);
	else if(objet=="EB") 		//Boss
		drawBoss(x,y);
	else if(objet=="B"){		//Bonus
		idx = instruction.find(delimiteur_parametre);
		int type = std::stoi(instruction.substr(0,idx));  
		drawBonus(type,x,y);
	}
}
void DisplayGame::parse_etat(std::string instruction){
	size_t idx;
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
void DisplayGame::starHandler(){
    
    stars.push_back(new vec2i{rand() % game_area.width(), 0});
    for(size_t i = 0; i < stars.size(); i++) {
            stars.at(i)->y += 1;
            if(stars.at(i)->y > game_area.bot() + 1)
                stars.erase(stars.begin() + i);

        }
}
void DisplayGame::drawStar() {
    for(auto s : stars){
        mvwaddch(game_wnd, s->y-1, s->x, '.');
    }

}

int DisplayGame::init() {

    srand(time(0)); // ??????

    main_wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    // hide cursor
    curs_set(0);

    // enable color modification
    start_color();


    // define area for screen (default terminal size)
    screen_area = { {0, 0}, {80, 24}};

    //wresize(main_wnd, screen_area.height(), screen_area.width());
    

    // initialize window areas
    int infopanel_height = 4;
    game_wnd = newwin( screen_area.height() - infopanel_height - 2,
                       screen_area.width() - 2,
                       screen_area.top() + 1,
                       screen_area.left() + 1);

    main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);
    
    // define area for movement
    game_area = { {0, 0}, {static_cast<uint_fast16_t>(screen_area.width() - 2), static_cast<uint_fast16_t>(screen_area.height() - infopanel_height - 4)}};

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    // enable function keys
    keypad(main_wnd, true);
    keypad(game_wnd, true);

    // disable input blocking
    nodelay(main_wnd, true);
    nodelay(game_wnd, true);


    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }
    return 0;
}
void DisplayGame::drawObstacle(int x, int y) {
    
	wattron(game_wnd, COLOR_PAIR(1));
	mvwaddch(game_wnd, y, x, '#');
	wattroff(game_wnd, COLOR_PAIR(1));
  
}
void DisplayGame::drawEnemy(int x, int y) {
    
	wattron(game_wnd, COLOR_PAIR(4));
	mvwaddch(game_wnd, y, x, '%');
	wattroff(game_wnd, COLOR_PAIR(4));


	wattron(game_wnd, A_ALTCHARSET);
	mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
	mvwaddch(game_wnd, y, x + 1, ACS_RARROW);
	wattroff(game_wnd, A_ALTCHARSET);


    for( PlayerShip* p : m->getListPlayer()) {
        if(listPlayer->at(p->getPlayerNb())->getnLives() > 0){
            if(tick % 20 < 10 && p->getHp()<=0 && tick<p->getKillTime()+100) {
                for(EnemyShip* e :m->getEnemy()){
                    wattron(game_wnd, COLOR_PAIR(4));
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x, ' ');
                    wattroff(game_wnd, COLOR_PAIR(4));

                    wattron(game_wnd, A_ALTCHARSET);
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ' ');
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ' ');
                    wattroff(game_wnd, A_ALTCHARSET);
                }
            }
        }
    }

}