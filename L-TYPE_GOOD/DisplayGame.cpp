
#include "DisplayGame.hpp"

void DisplayGame::parse_instruction(std::string chaine_instruction){  // A_B_type_x_y&E_H2_valeur&...
	//std::string chaine_instruction(buffer);
	eraseWnd();
	while(chaine_instruction.size() > 1){ 
		std::size_t idx = chaine_instruction.find(delimiteur_instruction);  //idx du premier delimiteur_instruction (&)
		std::string instruction = chaine_instruction.substr(0,idx);     	// on retire une instruction
		chaine_instruction = chaine_instruction.substr(idx+1,chaine_instruction.size()); // on garde la chaine sans l'instruction
		idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l'instruction
		std::string type_instruction = instruction.substr(0,idx); 		//on récupère le premier param de l'instruction
		instruction = instruction.substr(idx+1,instruction.size()); //on met à jour l'instruction
	
		if (type_instruction == "A") 		//Affichage
			parse_affichage(instruction);
		else if (type_instruction == "E")	//Etat
			parse_etat(instruction);

	}
	if (tickStar%7==0)
		starHandler();
	drawStar();
	tickStar++;
	usleep(1000);
	refreshWnd();
}

void DisplayGame::refreshWnd(){
	wrefresh(main_wnd);
    wrefresh(game_wnd);
}

void DisplayGame::eraseWnd(){
	
	werase(game_wnd);
	
}

void DisplayGame::close(){
    werase(game_wnd);
    werase(main_wnd);
    delwin(main_wnd);
    delwin(game_wnd);
    endwin();
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

	//dans l'ordre de réccurence (pour eviter trop de comparaison)
	if(objet=="PE") 			//projectile ennemi
		drawProjectile(x,y,true,false);
	else if(objet=="PJ")		//projectile joueur
		drawProjectile(x,y,false,true);
	else if(objet=="PJ2")		//projectile joueur
		drawProjectile(x,y,false,false);
	else if(objet=="E"){			//vaisseau ennemi
		int explo;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));	
		drawEnemy(x,y,explo, 1);
	}
	else if(objet=="E2"){			//vaisseau ennemi
		int explo;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));		
		drawEnemy(x,y,explo, 2);
	}
	else if(objet=="1"){		//vaisseau joueur 1     A_1_x_y_explosion_tick
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.length()));
		drawPlayer(1,x,y,tick,explo);
	}	

	else if(objet=="2"){		//vaisseau joueur 2
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.length()));
		drawPlayer(2,x,y,tick,explo);
	}			
	else if(objet=="O")			//obstacle
		drawObstacle(x,y);
	else if(objet=="EB") 		//Boss
		drawBoss(x,y,1);
	else if(objet=="EB2")
		drawBoss(x,y,2);
	else if(objet=="B"){		//Bonus
		idx = instruction.find(delimiteur_parametre);
		int type = std::stoi(instruction.substr(0,idx));  
		drawBonus(type,x,y);
	}
	else if (objet=="L"){
		idx = instruction.find(delimiteur_parametre);
		int currentLevel = std::stoi(instruction.substr(0,idx));
		drawNewLevel(x,y,currentLevel);
	}


}
void DisplayGame::parse_etat(std::string instruction){
	//E_2_HP2_Vies_Score_bonus_level_tick
	size_t idx;
	int player,hp, life, score,level,tick,bonustype;

	idx = instruction.find(delimiteur_parametre); 					//on va voir le premier param de l'instruction
	player = std::stoi(instruction.substr(0,idx)); 					//on récupère le premier param de l'instruction
	
	instruction = instruction.substr(idx+1,instruction.size()); 	//on nettoie l'instruction
	idx = instruction.find(delimiteur_parametre);
	hp = std::stoi(instruction.substr(0,idx)); 		

	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);
	life = std::stoi(instruction.substr(0,idx)); 	

	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);	
	score = std::stoi(instruction.substr(0,idx)); 

	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);
	bonustype = std::stoi(instruction.substr(0,idx));

	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);
	level = std::stoi(instruction.substr(0,idx));

	instruction = instruction.substr(idx+1,instruction.size()); 
	idx = instruction.find(delimiteur_parametre);
	tick = std::stoi(instruction.substr(0,idx));

	drawUi(player,hp, score, life,bonustype,level,tick);
}
void DisplayGame::starHandler(){
    //gère le défilement des étoiles en fond
    stars.push_back(new vec2i{static_cast<uint_fast16_t>(rand()) % game_area.width(), 0});
    for(size_t i = 0; i < stars.size(); i++) {
            stars.at(i)->y += 1;
            if(stars.at(i)->y > game_area.bot() + 1)
                stars.erase(stars.begin() + static_cast<std::vector<vec2i*>::difference_type>(i));

        }
}
void DisplayGame::drawStar() {
    for(auto s : stars){
        mvwaddch(game_wnd, static_cast<int>(s->y)-1, static_cast<int>(s->x), '.');
    }

}

void DisplayGame::drawNewLevel(int tick,int levelTick,int currentLevel) {
    if(levelTick != 0 && tick <= levelTick + 600 && tick > levelTick+100){
        mvwprintw(game_wnd, 8, 35, "level %i", currentLevel);
    }
}

int DisplayGame::init() {
    main_wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    // cache le curseur
    curs_set(0);

    // active la modification des couleurs
    start_color();

    // définit la zone de l'écran (taille du terminal par défaut)
    screen_area = { {0, 0}, {80, 24}};
    

    // initialisation des Window
    int infopanel_height = 4;
    game_wnd = newwin( static_cast<int>(screen_area.height()) - infopanel_height - 2,
                       static_cast<int>(screen_area.width() - 2),
                       static_cast<int>(screen_area.top() + 1),
                       static_cast<int>(screen_area.left() + 1));
    main_wnd = newwin(static_cast<int>(screen_area.height()), static_cast<int>(screen_area.width()), 0, 0);
    
    game_area = {{0, 0}, {78, 16}};

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
        printf("ERROR: Terminal does not support color.\n"); // [TODO] modifier printf
        exit(1);
    }

	wattron(main_wnd, A_BOLD);
    box(main_wnd, 0, 0);
    wattroff(main_wnd, A_BOLD);

    // horizontal line
    wmove(main_wnd, static_cast<int>(game_area.bot() + 3), 1);
    whline(main_wnd, '-', static_cast<int>(screen_area.width()- 2));

    // initial draw

    wrefresh(main_wnd);
    wrefresh(game_wnd);
    return 0;
}


void DisplayGame::drawObstacle(int x, int y) { 
	wattron(game_wnd, COLOR_PAIR(1));
	mvwaddch(game_wnd, y, x, '#');
	wattroff(game_wnd, COLOR_PAIR(1)); 
}


void DisplayGame::drawEnemy(int x, int y, bool isBlinking, int type) {   
	wattron(game_wnd, COLOR_PAIR(4));
	if(type == 1)
		mvwaddch(game_wnd, y, x, '%');
	else
		mvwaddch(game_wnd, y, x, '@');		
	wattroff(game_wnd, COLOR_PAIR(4));

	wattron(game_wnd, A_ALTCHARSET);
	mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
	mvwaddch(game_wnd, y, x + 1, ACS_RARROW);
	wattroff(game_wnd, A_ALTCHARSET);
	
	if(isBlinking){		
		wattron(game_wnd, COLOR_PAIR(4));
		mvwaddch(game_wnd, y, x, ' ');
		wattroff(game_wnd, COLOR_PAIR(4));

		wattron(game_wnd, A_ALTCHARSET);
		mvwaddch(game_wnd, y, x - 1, ' ');
		mvwaddch(game_wnd, y, x + 1, ' ');
		wattroff(game_wnd, A_ALTCHARSET);
	}
}


void DisplayGame::drawProjectile(int x, int y, bool enemy, bool player1){
	if(enemy){
		wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, y, x, '*');
        wattroff(game_wnd, COLOR_PAIR(4));
	}
	else if (player1) {
		wattron(game_wnd, COLOR_PAIR(5));
		mvwaddch(game_wnd, y, x, '*');
		wattroff(game_wnd, COLOR_PAIR(5));
	}
	else{
		wattron(game_wnd, COLOR_PAIR(2));
		mvwaddch(game_wnd, y, x, '*');
		wattroff(game_wnd, COLOR_PAIR(2));
	}            
}


void DisplayGame::drawPlayer(int player, int x , int y, int tick, bool isBlinking){
        int player_color;
		char player_char;
        if (player==1){
            player_color=5;
			player_char = '0';
        }
        else{
			player_color=2;
			player_char= '1';
		}
        wattron(game_wnd, COLOR_PAIR(player_color));
        mvwaddch(game_wnd, y, x, static_cast<chtype>(player_char));
        wattroff(game_wnd, COLOR_PAIR(player_color));

        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
        mvwaddch(game_wnd, y, x + 1, ACS_RARROW);	
		// dessine les flammes du réacteur
		if((tick % 10) / 3 && !isBlinking) {
                wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
                mvwaddch(game_wnd, y + 1, x, ACS_UARROW);
                mvwaddch(game_wnd, y + 1, x, ACS_UARROW);
                wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
            }

        if(isBlinking){
            // clignote si le joueur perd une vie et en a encore une ou plus
            if(tick % 100 < 50) {
                wattron(game_wnd, COLOR_PAIR(player_color));
                mvwaddch(game_wnd, y, x, ' ');
                wattroff(game_wnd, COLOR_PAIR(player_color));

                wattron(game_wnd, A_ALTCHARSET);
                mvwaddch(game_wnd, y, x - 1, ' ');
                mvwaddch(game_wnd, y, x + 1, ' ');
                wattroff(game_wnd, A_ALTCHARSET);
            }                   
        }
        wattroff(game_wnd, A_ALTCHARSET);
}


void DisplayGame::drawBonus(int type, int x, int y){
	wattron(game_wnd, A_BOLD);
	if(type==lifeSteal){
		mvwaddch(game_wnd, y, x, 'L');
	}
	else if(type==minigun){
		mvwaddch(game_wnd, y, x, 'M');
	}
	else if(type==damageUp){
		mvwaddch(game_wnd, y, x, 'D');
	}
	else if(type==tripleShot){
		mvwaddch(game_wnd, y, x, 'T');
	}
	wattroff(game_wnd, A_BOLD);
}


void DisplayGame::drawBoss(int x, int y, int type){
        wattron(main_wnd, COLOR_PAIR(4));
		if (type==2) {
		mvwprintw(game_wnd, y,   x, "      ______      ");
        mvwprintw(game_wnd, y+1, x, " ____|______|____");
        mvwprintw(game_wnd, y+2, x, "/ |____________| \\");
        mvwprintw(game_wnd, y+3, x, "| |____________| |");
        mvwprintw(game_wnd, y+4, x, "\\_|____ ___ ___|_/");
        mvwprintw(game_wnd, y+5, x, "  |_| |_| |_| |_|");
		}
        else {
        mvwprintw(game_wnd, y,   x, "      ______      ");
        mvwprintw(game_wnd, y+1, x, " ____|______|____");
        mvwprintw(game_wnd, y+2, x, "/ |____________| \\");
        mvwprintw(game_wnd, y+3, x, "| |____________| |");
        mvwprintw(game_wnd, y+4, x, "\\_|____ ___ ___|_/");
        mvwprintw(game_wnd, y+5, x, "      |_| |_|     "); 
		}
		wattroff(main_wnd, COLOR_PAIR(4));
}


void DisplayGame::drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick){
	if(player == 0){
		wmove(main_wnd, 20, 1);
		whline(main_wnd, ' ', 25); // la barre de vie mesure 25 de long
		wmove(main_wnd, 20, 1);
		drawEnergyBar(hp);

		//score
		mvwprintw(main_wnd, 22, 1, "  score: %i", score);
		mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
		mvwprintw(main_wnd, 21, 15, "lives: %i",lives);
		// pourcentage de vie (hp)
		wattron(main_wnd, A_BOLD);
		if(hp <= 25) {
			wattron(main_wnd, COLOR_PAIR(4));
			if(tick % 100 < 50)
				mvwprintw(main_wnd, 21, 9, "%i%%", hp);
			wattroff(main_wnd, COLOR_PAIR(4));
		} else
			mvwprintw(main_wnd, 21, 9, "%i%%", hp);
		wattroff(main_wnd, A_BOLD);

		//bonus
		if (bonusType == minigun)
			mvwprintw(main_wnd, 22, 16, "  B%d: M",player + 1);
		else if (bonusType == damageUp)
			mvwprintw(main_wnd, 22, 16, "  B%d: D",player + 1);
		else if (bonusType == tripleShot)
			mvwprintw(main_wnd,22, 16, "  B%d: T",player + 1);
		else if (bonusType == lifeSteal)
			mvwprintw(main_wnd, 22, 16, "  B%d: L",player + 1);
		else if (bonusType == noBonus)
			mvwprintw(main_wnd, 22, 16, "  B%d:  ",player + 1);
	}
    if(player == 1){
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25);
        wmove(main_wnd, 20, 54);
        drawEnergyBar(hp);

        mvwprintw(main_wnd, 22, 54, "  score: %i", score);
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 68, "lives: %i",lives);

		// pourcentage de vie (hp) joueur 2
        wattron(main_wnd, A_BOLD);
        if(hp <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 62, "%i%%", hp);
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 62, "%i%%", hp);
        wattroff(main_wnd, A_BOLD);

		// bonus joueur 2
        if (bonusType == minigun)
            mvwprintw(main_wnd, 22, 69, "  B%d: M", player + 1);
        else if (bonusType == damageUp)
            mvwprintw(main_wnd, 22, 69, "  B%d: D", player + 1);
        else if (bonusType == tripleShot)
            mvwprintw(main_wnd, 22, 69, "  B%d: T", player + 1);
        else if (bonusType == lifeSteal)
            mvwprintw(main_wnd, 22, 69, "  B%d: L", player + 1);
        else if (bonusType == noBonus)
            mvwprintw(main_wnd, 22, 69, "  B%d:  ", player + 1);
    }
    
    //level
	if (level < 5) // level 5 = jeu fini
    mvwprintw(main_wnd,20,33," LEVEL : %i", level);
}


void DisplayGame::drawEnergyBar(int a) {
    int col_pair = 1;
    for(int i = 0; i < a; i+=4) {
        if(i > 100)
            col_pair = 5; // blue
        else if(i > 50)
            col_pair = 2; // green
        else if(i > 25)
            col_pair = 3; // yellow
        else
            col_pair = 4; // red

        wattron(main_wnd, COLOR_PAIR(col_pair));
        wattron(main_wnd, A_BOLD);
        waddch(main_wnd, '/');
        wattroff(main_wnd, A_BOLD);
        wattroff(main_wnd, COLOR_PAIR(col_pair));
    }
}

void DisplayGame::drawEndGame(std::string score){
	int score1 = std::stoi(score);
	mvwprintw(game_wnd,8, 35,"GAME OVER");
    mvwprintw(game_wnd,9, 35,"SCORE : %i", score1);
    mvwprintw(game_wnd,12, 32,"press p to quit");
    refreshWnd();
    while(true){
        char in_char = static_cast<char>(wgetch(main_wnd));
        if(in_char == 'p')break;
    }
}
