//TODO:
// ajouter un tour de boucle pour l'affichage
// print lifebar boss

// 2 players input


#include "DisplayGame.hpp"

void DisplayGame::parse_instruction(std::string chaine_instruction){  // A_B_type_x_y&E_H2_valeur&...
	//std::string chaine_instruction(buffer);
	eraseWnd();
	while(chaine_instruction.size() > 1){
		std::size_t idx = chaine_instruction.find(delimiteur_instruction);  //idx du premier delimiteur_instruction (&)
		std::string instruction = chaine_instruction.substr(0,idx);     	// on retire une instruction
		chaine_instruction = chaine_instruction.substr(idx+1,chaine_instruction.size()); // on garde la chaine sans l instruction
		idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
		std::string type_instruction = instruction.substr(0,idx); 		//on recupère le premier param de l instruction
		instruction = instruction.substr(idx+1,instruction.size()); //on met à jour l'instruction

		if (type_instruction == "A") 		//Affichage (utiliser des thread?)
			parse_affichage(instruction);
		else if (type_instruction == "E")	//Etat
			parse_etat(instruction);

	}
	if (tickStar%2==0)
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
int DisplayGame::getInputWindow(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		return 'q';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		return 'z';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		return 's';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		return 'd';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		return 'e';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		return 'a';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		return 'w';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		return 'c';
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		return 'q';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		return 'z';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		return 'f';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		return 't';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		return 'g';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		return 'h';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		return 'r';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		return 'y';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		return 'n';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		return 'v';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		return 'm';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return ' ';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		return 'p';
	}
	else{
		return -1;
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
		drawProjectile(x,y,true,false);
	else if(objet=="PJ")		//projectile joueur
		drawProjectile(x,y,false,true);
	else if(objet=="PJ2")		//projectile joueur
		drawProjectile(x,y,false,false);
	else if(objet=="E"){			//Vaisseau ennemie
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.size()));
		drawEnemy(x,y,tick,explo);
	}
	else if(objet=="1"){		//Vaisseau joueur 1     A_1_x_y_explosion_tick
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.length()));
		drawPlayer(1,x,y,tick,explo);
	}

	else if(objet=="2"){		//Vaisseau joueur 2
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.length()));
		drawPlayer(2,x,y,tick,explo);
	}
	else if(objet=="O")			//obstacle
		drawObstacle(x,y);
	else if(objet=="EB") 		//Boss
		drawBoss(x,y);
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

	idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
	player = std::stoi(instruction.substr(0,idx)); 		//on recupère le premier param de l instruction

	instruction = instruction.substr(idx+1,instruction.size()); //nettoie instruction
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

    stars.push_back(new vec2i{rand() % window->getSize().x, 0});
    for(size_t i = 0; i < stars.size(); i++) {
            stars.at(i)->y += 20;
            if(stars.at(i)->y > 370)
                stars.erase(stars.begin() + i);
        }
}
void DisplayGame::drawStar() {
    for(auto s : stars){
        //mvwaddch(game_wnd, s->y-1, s->x, '.');
		sf::CircleShape shape(2.f);
		shape.setPosition(sf::Vector2f(s->x, s->y));
		// change la couleur de la forme pour du vert
		shape.setFillColor(sf::Color::White);
		window->draw(shape);
    }

}

void DisplayGame::drawNewLevel(int tick,int levelTick,int currentLevel) {
    if(levelTick != 0 && tick <= levelTick + 600 && tick > levelTick+100){
		guiText.setString("Level " + std::to_string(currentLevel));
		guiText.setColor(sf::Color::White);
		guiText.setCharacterSize(22);
		guiText.setPosition(sf::Vector2f(35*12.5, 8*20));
		window->draw(guiText);

        mvwprintw(game_wnd, 8, 35, "level %i", currentLevel);
    }
}
void DisplayGame::initGraphics(){
	window = new sf::RenderWindow(sf::VideoMode(1000, 480), "L-TYPE");
	window->setVerticalSyncEnabled(false);
	
	if (!texture.loadFromFile("healthbar.png"))
	{
		// error...
	}
	
	if (!heart.loadFromFile("heart.png"))
	{
		// error...
	}
	
	if (!font.loadFromFile("space_age.ttf"))
	{
		// erreur...
	}

	if (!asteroid.loadFromFile("asteroid.png"))
	{
		// erreur...
	}

	if (!ship1.loadFromFile("player1.png"))
	{
		// erreur...
	}
	if (!ship2.loadFromFile("player2.png"))
	{
		// erreur...
	}
	if (!laser.loadFromFile("laser.png"))
	{
		// erreur...
	}
	if (!laser1.loadFromFile("laser1.png"))
	{
		// erreur...
	}
	if (!laser2.loadFromFile("laser2.png"))
	{
		// erreur...
	}
	if (!tripleshotTex.loadFromFile("tripleshot.png"))
	{
		// erreur...
	}if (!damageupTex.loadFromFile("damageup.png"))
	{
		// erreur...
	}if (!lifestealTex.loadFromFile("lifesteal.png"))
	{
		// erreur...
	}if (!minigunTex.loadFromFile("minigun.png"))
	{
		// erreur...
	}
	if (!enemy.loadFromFile("enemy.png"))
	{
		// erreur...
	}
	if (!boss.loadFromFile("boss.png"))
	{
		// erreur...
	}

	heartSprite.setScale(sf::Vector2f(0.03,0.03));
	heartSprite.setTexture(heart);

	health_bar.setScale(sf::Vector2f(0.22,0.22));
	health_bar.setTexture(texture);

	health_bar2.setScale(sf::Vector2f(0.22,0.22));
	health_bar2.setTexture(texture);

	asteroidSprite.setScale(sf::Vector2f(0.14, 0.16));
	asteroidSprite.setTexture(asteroid);

	ship1Sprite.setScale(sf::Vector2f(0.19,0.19));
	ship1Sprite.setTexture(ship1);

	ship2Sprite.setScale(sf::Vector2f(0.19,0.19));
	ship2Sprite.setTexture(ship2);

	laserSprite.setScale(sf::Vector2f(0.06,0.04));
	laserSprite.setRotation(1.5);
	laserSprite.setTexture(laser);

	laser1Sprite.setScale(sf::Vector2f(0.06,0.04));
	laser1Sprite.setRotation(1.5);
	laser1Sprite.setTexture(laser1);

	laser2Sprite.setScale(sf::Vector2f(0.06,0.04));
	laser2Sprite.setRotation(1.5);
	laser2Sprite.setTexture(laser2);

	tripleshotSprite.setScale(sf::Vector2f(0.12,0.12));
	tripleshotSprite.setTexture(tripleshotTex);

	damageupSprite.setScale(sf::Vector2f(0.12,0.12));
	damageupSprite.setTexture(damageupTex);

	lifestealSprite.setScale(sf::Vector2f(0.12,0.12));
	lifestealSprite.setTexture(lifestealTex);

	minigunSprite.setScale(sf::Vector2f(0.12,0.12));
	minigunSprite.setTexture(minigunTex);

	enemySprite.setScale(sf::Vector2f(0.16,0.22));
	enemySprite.setRotation(180);
	enemySprite.setTexture(enemy);

	bossSprite.setScale(sf::Vector2f(0.9,0.8));
	bossSprite.setRotation(180);
	bossSprite.setTexture(boss);

	guiText.setFont(font);

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

	wattron(main_wnd, A_BOLD);
    box(main_wnd, 0, 0);
    wattroff(main_wnd, A_BOLD);

    // horizontal diving line
    wmove(main_wnd, game_area.bot() + 3, 1);
    whline(main_wnd, '-', screen_area.width()- 2);

    // initial draw

    wrefresh(main_wnd);
    wrefresh(game_wnd);

    return 0;

}
void DisplayGame::drawObstacle(int x, int y) {

	wattron(game_wnd, COLOR_PAIR(1));
	mvwaddch(game_wnd, y, x, '#');
	wattroff(game_wnd, COLOR_PAIR(1));
	asteroidSprite.setPosition(sf::Vector2f((x+1)*12.5-4.5,y*20));
	sf::RectangleShape asteroidShape(sf::Vector2f(12.5*1.5,20*1.5));
	asteroidShape.setFillColor(sf::Color(102,51,0));
	asteroidShape.setPosition(sf::Vector2f((x+1)*12.5-3,y*20));
	
	if(y*20 < 350)
		window->draw(asteroidSprite);

}
void DisplayGame::drawEnemy(int x, int y, int tick, bool isBlinking) {

	wattron(game_wnd, COLOR_PAIR(4));
	mvwaddch(game_wnd, y, x, '%');
	wattroff(game_wnd, COLOR_PAIR(4));


	wattron(game_wnd, A_ALTCHARSET);
	mvwaddch(game_wnd, y, x - 1, ACS_LARROW);
	mvwaddch(game_wnd, y, x + 1, ACS_RARROW);
	wattroff(game_wnd, A_ALTCHARSET);


    //ajouter isBlinking chez le server
	if(isBlinking){


		wattron(game_wnd, COLOR_PAIR(4));
		mvwaddch(game_wnd, y, x, ' ');
		wattroff(game_wnd, COLOR_PAIR(4));

		wattron(game_wnd, A_ALTCHARSET);
		mvwaddch(game_wnd, y, x - 1, ' ');
		mvwaddch(game_wnd, y, x + 1, ' ');
		wattroff(game_wnd, A_ALTCHARSET);


	}
	sf::RectangleShape enemyShape(sf::Vector2f(12.5*3,20));
	enemyShape.setFillColor(sf::Color::Red);
	enemyShape.setPosition(sf::Vector2f(x*12.5,5 + y*20));
	enemySprite.setPosition(sf::Vector2f(x*12.5+ 60 ,5 + y*20 + 60));
	if(y*20 < 350){
		//window->draw(enemyShape);
		window->draw(enemySprite);
	}

}
void DisplayGame::drawProjectile(int x, int y, bool enemy, bool player1){
	sf::RectangleShape projectileShape(sf::Vector2f(12.5,20));
	
	projectileShape.setPosition(sf::Vector2f((x+1)*12.5,5 + y*20));
	
	
	if(enemy){
		projectileShape.setFillColor(sf::Color::Red);
		wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, y, x, '*');
        wattroff(game_wnd, COLOR_PAIR(4));
		laserSprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laserSprite);
		
	}
	else if (player1) {
		projectileShape.setFillColor(sf::Color::Blue);
		wattron(game_wnd, COLOR_PAIR(5));
		mvwaddch(game_wnd, y, x, '*');
		wattroff(game_wnd, COLOR_PAIR(5));
		laser1Sprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laser1Sprite);

	}
	else{
		projectileShape.setFillColor(sf::Color::Green);
		wattron(game_wnd, COLOR_PAIR(2));
		mvwaddch(game_wnd, y, x, '*');
		wattroff(game_wnd, COLOR_PAIR(2));
		laser2Sprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laser2Sprite);
		
	}
	//window->draw(projectileShape);
	
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

		sf::RectangleShape playerShipShape(sf::Vector2f(12.5*3,20*2));
		playerShipShape.setPosition(sf::Vector2f(x*12.5,5 + y*20));
		
		if (player==1){
            playerShipShape.setFillColor(sf::Color::Blue);
			ship1Sprite.setPosition(sf::Vector2f(x*12.5-30,5 + y*20-25));
			window->draw(ship1Sprite);
        }
        else{
			playerShipShape.setFillColor(sf::Color::Green);
			ship2Sprite.setPosition(sf::Vector2f(x*12.5-30,5 + y*20-25));
			window->draw(ship2Sprite);
		}
		
		//window->draw(playerShipShape);
		


}
void DisplayGame::drawBonus(int type, int x, int y){
	sf::RectangleShape bonusShape(sf::Vector2f(12.5,20));
	bonusShape.setFillColor(sf::Color::Yellow);
	bonusShape.setPosition(sf::Vector2f((x+1)*12.5,5 + y*20));
	if(y*20 < 350){
		//window->draw(bonusShape);
		wattron(game_wnd, A_BOLD);
		if(type==lifeSteal){
			mvwaddch(game_wnd, y, x, 'L');
			lifestealSprite.setPosition(sf::Vector2f((x+1)*12.5-11,y*20-15));
			window->draw(lifestealSprite);
		}
		else if(type==minigun){
			mvwaddch(game_wnd, y, x, 'M');
			minigunSprite.setPosition(sf::Vector2f((x+1)*12.5-11,y*20-15));
			window->draw(minigunSprite);
		}
		else if(type==damageUp){
			mvwaddch(game_wnd, y, x, 'D');
			damageupSprite.setPosition(sf::Vector2f((x+1)*12.5-11,y*20-15));
			window->draw(damageupSprite);
		}
		else if(type==tripleShot){
			mvwaddch(game_wnd, y, x, 'T');
			tripleshotSprite.setPosition(sf::Vector2f((x+1)*12.5-11,y*20-15));
			window->draw(tripleshotSprite);
		}
		wattroff(game_wnd, A_BOLD);
	}
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
		sf::RectangleShape bossShape(sf::Vector2f(12.5*18,20*6));
		bossShape.setFillColor(sf::Color::Red);
		bossShape.setPosition(sf::Vector2f(x*12.5+7,5 + y*20));
		bossSprite.setPosition(sf::Vector2f(x*12.5+7 +340,5 + y*20 + 260));
		//window->draw(bossShape);
		window->draw(bossSprite);
}
void DisplayGame::drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick){
		sf::RectangleShape cadre(sf::Vector2f(990, 470));
		cadre.setFillColor(sf::Color::Transparent);
		cadre.setOutlineThickness(2);
		cadre.setOutlineColor(sf::Color::Magenta);
		cadre.setPosition(sf::Vector2f(5, 5));
		window->draw(cadre);

		sf::RectangleShape line(sf::Vector2f(990, 2));
		line.setFillColor(sf::Color::Magenta);
		//cadre.setOutlineColor(sf::Color::Cyan);
		line.setPosition(sf::Vector2f(5, 370));
		window->draw(line);


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



		//healthbar
		health_bar.setPosition(sf::Vector2f(3,380));
		window->draw(health_bar);
		sf::IntRect rect (0,0,200+((texture.getSize().x-200)/100)*hp,texture.getSize().y); //200=0
		health_bar.setTextureRect(rect);
		//score
		guiText.setString("Score: "+std::to_string(score));
		guiText.setCharacterSize(20); 
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(13,440));
		window->draw(guiText);
		//life
		guiText.setString(std::to_string(hp)+"%");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(83,386));
		window->draw(guiText);
		//n lives
		guiText.setString("P1");
		guiText.setCharacterSize(19); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(15,387));
		window->draw(guiText);
		//Bonus
		if (bonusType == minigun)
			guiText.setString("  B"+std::to_string(player+1)+":M");
		else if (bonusType == damageUp)
			guiText.setString("  B"+std::to_string(player+1)+":D");
		else if (bonusType == tripleShot)
			guiText.setString("  B"+std::to_string(player+1)+":T");
		else if (bonusType == lifeSteal)
			guiText.setString("  B"+std::to_string(player+1)+":L");
		else if (bonusType == noBonus)
			guiText.setString("  B"+std::to_string(player+1)+": ");
		guiText.setCharacterSize(20); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(100,418));
		window->draw(guiText);
		// hearts
		if (lives>=1)
		{
			heartSprite.setPosition(sf::Vector2f(15,420));
			window->draw(heartSprite);
			if(lives>=2)
			{
				heartSprite.setPosition(sf::Vector2f(45,420));
				window->draw(heartSprite);
				if(lives==3)
				{
					heartSprite.setPosition(sf::Vector2f(75,420));
					window->draw(heartSprite);
				}
			}
		}
		
		


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

		health_bar2.setPosition(sf::Vector2f(460,380));
		window->draw(health_bar2);
		sf::IntRect rect (0,0,200+((texture.getSize().x-200)/100)*hp,texture.getSize().y); //200=0
		health_bar2.setTextureRect(rect);

		//score
		guiText.setString("Score: "+std::to_string(score));
		guiText.setCharacterSize(20); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(470,440));
		window->draw(guiText);
		//life
		guiText.setString(std::to_string(hp)+"%");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(546,386));
		window->draw(guiText);
		//n lives
		guiText.setString("P2");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(468,387));
		window->draw(guiText);
		//Bonus
		if (bonusType == minigun)
			guiText.setString("  B"+std::to_string(player+1)+":M");
		else if (bonusType == damageUp)
			guiText.setString("  B"+std::to_string(player+1)+":D");
		else if (bonusType == tripleShot)
			guiText.setString("  B"+std::to_string(player+1)+":T");
		else if (bonusType == lifeSteal)
			guiText.setString("  B"+std::to_string(player+1)+":L");
		else if (bonusType == noBonus)
			guiText.setString("  B"+std::to_string(player+1)+": ");
		guiText.setCharacterSize(20); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(557,418));
		window->draw(guiText);
		// hearts
		if (lives>=1)
		{
			heartSprite.setPosition(sf::Vector2f(472,420));
			window->draw(heartSprite);
			if(lives>=2)
			{
				heartSprite.setPosition(sf::Vector2f(502,420));
				window->draw(heartSprite);
				if(lives==3)
				{
					heartSprite.setPosition(sf::Vector2f(532,420));
					window->draw(heartSprite);
				}
			}
		}

    }

    //level
    mvwprintw(main_wnd,20,33," LEVEL : %i", level);
	guiText.setString("Level "+std::to_string(level));
	guiText.setCharacterSize(20);
	guiText.setColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(275,380));
	window->draw(guiText);


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

	guiText.setString("GAME OVER");
	guiText.setCharacterSize(20);
	guiText.setColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(35*12.5, 8*20));
	window->draw(guiText);



	guiText.setString("SCORE : "+score);
	guiText.setPosition(sf::Vector2f(35*12.5, 9*20));
	window->draw(guiText);


	guiText.setString("press p to quit");
	guiText.setColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(32*12.5, 12*20));
	window->draw(guiText);

	mvwprintw(game_wnd,8, 35,"GAME OVER");
    mvwprintw(game_wnd,9, 35,"SCORE : %i", std::stoi(score));
    mvwprintw(game_wnd,12, 32,"press p to quit");
    refreshWnd();
    
}
