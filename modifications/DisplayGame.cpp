
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
void DisplayGame::drawEnemy(int x, int y, int tick, bool isBlinking) {
    
	wattron(game_wnd, COLOR_PAIR(4));
	mvwaddch(game_wnd, y, x, '%');
	wattroff(game_wnd, COLOR_PAIR(4));


	wattron(game_wnd, A_ALTCHARSET);
	mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
	mvwaddch(game_wnd, y, x + 1, ACS_RARROW);
	wattroff(game_wnd, A_ALTCHARSET);

	
    //ajouter isBlinking chez le serveur
	if(isBlinking){
		if(tick % 20 < 10) {
			
			wattron(game_wnd, COLOR_PAIR(4));
			mvwaddch(game_wnd, y, x, ' ');
			wattroff(game_wnd, COLOR_PAIR(4));

			wattron(game_wnd, A_ALTCHARSET);
			mvwaddch(game_wnd, y, x - 1, ' ');
			mvwaddch(game_wnd, y, x + 1, ' ');
			wattroff(game_wnd, A_ALTCHARSET);
			
		}
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

        // draw player body
        int player_color;
		char player_char;
        if (player==1){
            player_color=2;
			player_char = '1';
        }
        else{
			player_color=5;
			player_char= '0';
		}
        wattron(game_wnd, COLOR_PAIR(player_color));
        mvwaddch(game_wnd, y, x, player_char);
        wattroff(game_wnd, COLOR_PAIR(player_color));

        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
        mvwaddch(game_wnd, y, x + 1, ACS_RARROW);
		//ajouter isBlinking chez le serveur	
		// draw engines flames
		if((tick % 10) / 3 && !isBlinking) {
                wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
                mvwaddch(game_wnd, y + 1, x, ACS_UARROW);
                mvwaddch(game_wnd, y + 1, x, ACS_UARROW);
                wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
            }

        if(isBlinking){
            // show player looses a life
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

void DisplayGame::drawBoss(int x, int y){
        wattron(main_wnd, COLOR_PAIR(4));
        mvwprintw(game_wnd, y,   x, "      ______      ");
        mvwprintw(game_wnd, y+1, x, " ____|______|____");
        mvwprintw(game_wnd, y+2, x, "/ |____________| \\");
        mvwprintw(game_wnd, y+3, x, "| |____________| |");
        mvwprintw(game_wnd, y+4, x, "\\_|____ ___ ___|_/");
        mvwprintw(game_wnd, y+5, x, "      |_| |_|     ");
        wattroff(main_wnd, COLOR_PAIR(4));
}
void DisplayGame::drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick){
	if(player == 0){
		wmove(main_wnd, 20, 1);
		whline(main_wnd, ' ', 25); // health bar is 25 chars long
		wmove(main_wnd, 20, 1);
		drawEnergyBar(hp);
		//score
		mvwprintw(main_wnd, 22, 1, "  score: %i", score);
		// draw static string to hold percentage
		mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
		mvwprintw(main_wnd, 21, 15, "lives: %i",lives);
		// draw numeric percentage player 1
		wattron(main_wnd, A_BOLD);
		if(hp <= 25) {
			wattron(main_wnd, COLOR_PAIR(4));
			if(tick % 100 < 50)
				mvwprintw(main_wnd, 21, 9, "%i%%", hp);
			wattroff(main_wnd, COLOR_PAIR(4));
		} else
			mvwprintw(main_wnd, 21, 9, "%i%%", hp);
		wattroff(main_wnd, A_BOLD);
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
        // energy bar player2
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 54);
        drawEnergyBar(hp);
        //score  
        mvwprintw(main_wnd, 22, 54, "  score: %i", score);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 68, "lives: %i",lives);
        // draw numeric percentage player 2
        wattron(main_wnd, A_BOLD);
        if(hp <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 62, "%i%%", hp);
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 62, "%i%%", hp);
        wattroff(main_wnd, A_BOLD);
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