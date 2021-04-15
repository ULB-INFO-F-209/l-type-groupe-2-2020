//TODO:
// exlosion finale (2P)
// print lifebar boss


#include "DisplayGame.hpp"

void DisplayGame::parse_instruction(std::string chaine_instruction){  // A_B_type_x_y&E_H2_valeur&...
	//std::string chaine_instruction(buffer);
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
}


int DisplayGame::getInputWindow(std::vector<int> *inp){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		inp->push_back('q');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		inp->push_back('z');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		inp->push_back('s');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		inp->push_back('d');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		inp->push_back('e');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		inp->push_back('a');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		inp->push_back('w');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		inp->push_back('c');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		inp->push_back('f');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		inp->push_back('t');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		inp->push_back('g');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		inp->push_back('h');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		inp->push_back('r');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		inp->push_back('y');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		inp->push_back('n');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		inp->push_back('v');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		inp->push_back('m');
		if(twoPlayer)
			laserSound.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		inp->push_back(' ');
		laserSound.play();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		inp->push_back('p');
		return('p');
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
	if(objet=="PE") 			//projectile ennemi
		drawProjectile(x,y,true,false);
	else if(objet=="PJ")		//projectile joueur
		drawProjectile(x,y,false,true);
	else if(objet=="PJ2")		//projectile joueur
		drawProjectile(x,y,false,false);
	else if(objet=="E"){			//Vaisseau ennemi
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.size()));
		drawEnemy(x,y,tick,explo, 1);
	}
	else if(objet=="E2"){			//Vaisseau ennemie
		int explo,tick;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		tick = std::stoi(instruction.substr(idx+1,instruction.size()));
		drawEnemy(x,y,tick,explo, 2);
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
		sf::CircleShape shape(2.f);
		shape.setPosition(sf::Vector2f(s->x, s->y));
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
    }
}
void DisplayGame::initGraphics(){
	window = new sf::RenderWindow(sf::VideoMode(1000, 480), "L-TYPE");
/*
	sf::Vector2f viewCenter(500, 240);
	sf::Vector2f viewHalfSize(1000, 480);
	sf::View mainView(viewCenter, viewHalfSize);
	window->setView(mainView);
	
*/

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
	if (!boss.loadFromFile("boss2.png"))
	{
		// erreur...
	}
	if (!enemyH.loadFromFile("enemy2.png"))
	{
		// erreur...
	}
	if (!boss2.loadFromFile("boss.png"))
	{
		// erreur...
	}
	if (!explosionTex.loadFromFile("explosion_effect.png"))
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

	ship1Sprite.setScale(sf::Vector2f(0.22,0.30));
	ship1Sprite.setTexture(ship1);

	ship2Sprite.setScale(sf::Vector2f(0.22,0.30));
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

	tripleshotSprite.setScale(sf::Vector2f(0.07,0.07));
	tripleshotSprite.setTexture(tripleshotTex);

	damageupSprite.setScale(sf::Vector2f(0.07,0.07));
	damageupSprite.setTexture(damageupTex);

	lifestealSprite.setScale(sf::Vector2f(0.12,0.12));
	lifestealSprite.setTexture(lifestealTex);

	minigunSprite.setScale(sf::Vector2f(0.07,0.07));
	minigunSprite.setTexture(minigunTex);

	enemySprite.setScale(sf::Vector2f(0.16,0.22));
	enemySprite.setRotation(180);
	enemySprite.setTexture(enemy);

	bossSprite.setScale(sf::Vector2f(0.9,0.8));
	bossSprite.setRotation(180);
	bossSprite.setTexture(boss);

	enemyHSprite.setScale(sf::Vector2f(0.16,0.22));
	enemyHSprite.setRotation(180);
	enemyHSprite.setTexture(enemyH);

	boss2Sprite.setScale(sf::Vector2f(0.9,0.8));
	boss2Sprite.setRotation(180);
	boss2Sprite.setTexture(boss2);
	
	line.setFillColor(sf::Color::Magenta);
	line.setPosition(sf::Vector2f(5, 370));

	explosionSprite1.setTexture(explosionTex);
	explosionSprite1.setTextureRect(rectSourceSprite1);

	explosionSprite2.setTexture(explosionTex);
	explosionSprite2.setTextureRect(rectSourceSprite2);
	
	
	if (!music.openFromFile("song.ogg"))
		{
			std::cout<<"PAS DE SON"<<std::endl;
		}
	if (!buffer.loadFromFile("laserSound.wav"))
		{
			std::cout<<"PAS DE LASER"<<std::endl;
		}
	if (!buffer1.loadFromFile("explosionSound.wav"))
		{
			std::cout<<"PAS D'EXPLOSION"<<std::endl;
		}

	laserSound.setBuffer(buffer);
	explosionSound.setBuffer(buffer1);
	//music.setVolume (100.0f);
	music.play();
	music.setLoop(true);
	guiText.setFont(font);

}

void DisplayGame::drawObstacle(int x, int y) {

	asteroidSprite.setPosition(sf::Vector2f((x+1)*12.5-4.5,y*20));
	//sf::RectangleShape asteroidShape(sf::Vector2f(12.5*1.5,20*1.5));
	//asteroidShape.setFillColor(sf::Color(102,51,0));
	//asteroidShape.setPosition(sf::Vector2f((x+1)*12.5-3,y*20));
	if(y*20 < 350)
		window->draw(asteroidSprite);

}
void DisplayGame::drawEnemy(int x, int y, int tick, bool isBlinking, int type) {

	if(type == 1){
		if(isBlinking){

			enemySprite.setColor(sf::Color::Red);

		}
		else{
			enemySprite.setColor(sf::Color::White); //default color
		}
		
		//sf::RectangleShape enemyShape(sf::Vector2f(12.5*3,20));
		//enemyShape.setFillColor(sf::Color::Red);
		//enemyShape.setPosition(sf::Vector2f(x*12.5,5 + y*20));
		enemySprite.setPosition(sf::Vector2f(x*12.5+ 60 ,5 + y*20 + 60));
		if(y*20 < 350){
			//window->draw(enemyShape);
			window->draw(enemySprite);
		}
	}
	else{
		if(isBlinking){

			enemyHSprite.setColor(sf::Color::Red);

		}
		else{
			enemyHSprite.setColor(sf::Color::White); //default color
		}
		
		//sf::RectangleShape enemyShape(sf::Vector2f(12.5*3,20));
		//enemyShape.setFillColor(sf::Color::Red);
		//enemyShape.setPosition(sf::Vector2f(x*12.5,5 + y*20));
		enemyHSprite.setPosition(sf::Vector2f(x*12.5+ 60 ,5 + y*20 + 60));
		if(y*20 < 350){
			//window->draw(enemyShape);
			window->draw(enemyHSprite);
		}
	}

}
void DisplayGame::drawProjectile(int x, int y, bool enemy, bool player1){
	//sf::RectangleShape projectileShape(sf::Vector2f(12.5,20));

	//projectileShape.setPosition(sf::Vector2f((x+1)*12.5,5 + y*20));


	if(enemy){
		//projectileShape.setFillColor(sf::Color::Red);
		laserSprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laserSprite);

	}
	else if (player1) {
		//projectileShape.setFillColor(sf::Color::Blue);

		laser1Sprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laser1Sprite);

	}
	else{
		//projectileShape.setFillColor(sf::Color::Green);
		laser2Sprite.setPosition(sf::Vector2f((x+1)*12.5+1,y*20+5));
		window->draw(laser2Sprite);

	}
	//window->draw(projectileShape);

}
void DisplayGame::drawPlayer(int player, int x , int y, int tick, bool isBlinking){

		
        if(isBlinking){
            // show player looses a life
			
			if(player==1){
				
				if(clock1.getElapsedTime().asSeconds() > 0.025f && !exploded1){
					if(rectSourceSprite1.left==1792 && rectSourceSprite1.top==1280){
						rectSourceSprite1.left=0;
						rectSourceSprite1.top=0;
						exploded1=true;

					}
					if (rectSourceSprite1.left==1792){
						rectSourceSprite1.left=0;
						rectSourceSprite1.top+=256;
					}
					else
						rectSourceSprite1.left +=256;
					
					explosionSprite1.setTextureRect(rectSourceSprite1);
					clock1.restart();
				}
				if(!exploded1){
					if (!explo1PosSaved)
						explosionSprite1.setPosition(sf::Vector2f(x*12.5-125,5 + y*20-110));
						explo1PosSaved=true;
					if(!soundExploded1){
						explosionSound.play();
						soundExploded1=true;
					}
					window->draw(explosionSprite1);
					
						
				}
				
					
			}
			else{
				if(clock2.getElapsedTime().asSeconds() > 0.025f && !exploded2){
					if(rectSourceSprite2.left==1792 && rectSourceSprite2.top==1280){
						rectSourceSprite2.left=0;
						rectSourceSprite2.top=0;
						exploded2=true;

					}
					if (rectSourceSprite2.left==1792){
						rectSourceSprite2.left=0;
						rectSourceSprite2.top+=256;
					}
					else
						rectSourceSprite2.left +=256;
					
					explosionSprite2.setTextureRect(rectSourceSprite2);
					clock2.restart();
				}
				if(!exploded2){
					if (!explo2PosSaved)
						explosionSprite2.setPosition(sf::Vector2f(x*12.5-125,5 + y*20-110));
						explo2PosSaved=true;
					if(!soundExploded2){
						explosionSound.play();
						soundExploded2=true;
					}
					window->draw(explosionSprite2);
					

				}
			}

        }
		else{
			if(player==1 && exploded1){
				exploded1=false;
				explo1PosSaved=false;
				soundExploded1=false;
			} 
			if(player==2 && exploded2){
				exploded2=false;
				explo2PosSaved=false;
				soundExploded2=false;


			} 

		}		

		//sf::RectangleShape playerShipShape(sf::Vector2f(12.5*3,20*2));
		//playerShipShape.setPosition(sf::Vector2f(x*12.5,5 + y*20));
        //window->draw(playerShipShape);
		if (player==1 && !isBlinking){
            //playerShipShape.setFillColor(sf::Color::Blue);
			ship1Sprite.setPosition(sf::Vector2f(x*12.5-36.5,5 + y*20-55));
			window->draw(ship1Sprite);
        }
		else if (player==1 && isBlinking && tick % 80 < 40 && exploded1){
			ship1Sprite.setPosition(sf::Vector2f(x*12.5-36.5,5 + y*20-55));
			window->draw(ship1Sprite);
		}

        else if (player==2 && !isBlinking){
			//playerShipShape.setFillColor(sf::Color::Green);
			ship2Sprite.setPosition(sf::Vector2f(x*12.5-36.5,5 + y*20-55));
			window->draw(ship2Sprite);
		}
		else if (player==2 && isBlinking && tick % 80 < 40 && exploded2){
			ship2Sprite.setPosition(sf::Vector2f(x*12.5-36.5,5 + y*20-55));
			window->draw(ship2Sprite);
		}




}
void DisplayGame::drawBonus(int type, int x, int y){
	//sf::RectangleShape bonusShape(sf::Vector2f(12.5,20));
	//bonusShape.setFillColor(sf::Color::Yellow);
	//bonusShape.setPosition(sf::Vector2f((x+1)*12.5,5 + y*20));
	if(y*20 < 350){
		//window->draw(bonusShape);
		if(type==lifeSteal){
			lifestealSprite.setPosition(sf::Vector2f((x+1)*12.5-11,y*20-15));
			window->draw(lifestealSprite);
		}
		else if(type==minigun){
			minigunSprite.setPosition(sf::Vector2f((x+1)*12.5-12,y*20-15));
			window->draw(minigunSprite);
		}
		else if(type==damageUp){
			damageupSprite.setPosition(sf::Vector2f((x+1)*12.5-12,y*20-15));
			window->draw(damageupSprite);
		}
		else if(type==tripleShot){
			tripleshotSprite.setPosition(sf::Vector2f((x+1)*12.5-12,y*20-15));
			window->draw(tripleshotSprite);
		}
	}
}

void DisplayGame::drawBoss(int x, int y, int type){
		//sf::RectangleShape bossShape(sf::Vector2f(12.5*18,20*6));
		//bossShape.setFillColor(sf::Color::Red);
		//bossShape.setPosition(sf::Vector2f(x*12.5+7,5 + y*20));
		if(type == 1){
			bossSprite.setPosition(sf::Vector2f(x*12.5+7 +340,5 + y*20 + 260));
			//window->draw(bossShape);
			window->draw(bossSprite);
		}else{
			boss2Sprite.setPosition(sf::Vector2f(x*12.5+7 +340,5 + y*20 + 260));
			//window->draw(bossShape);
			window->draw(boss2Sprite);
		}
}
void DisplayGame::drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick){
		
		/*
		sf::RectangleShape cadre(sf::Vector2f(990, 470));
		cadre.setFillColor(sf::Color::Transparent);
		cadre.setOutlineThickness(2);
		cadre.setOutlineColor(sf::Color::Magenta);
		cadre.setPosition(sf::Vector2f(5, 5));
		window->draw(cadre);
		*/
		window->draw(line);
		

	if(player == 0){	
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
		twoPlayer=true;
		//healthbar
		health_bar2.setPosition(sf::Vector2f(460+325,380));
		window->draw(health_bar2);
		sf::IntRect rect (0,0,200+((texture.getSize().x-200)/100)*hp,texture.getSize().y); //200=0
		health_bar2.setTextureRect(rect);

		//score
		guiText.setString("Score: "+std::to_string(score));
		guiText.setCharacterSize(20); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(470+325,440));
		window->draw(guiText);
		//life
		guiText.setString(std::to_string(hp)+"%");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(546+325,386));
		window->draw(guiText);
		//n lives
		guiText.setString("P2");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(468+325,387));
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
		guiText.setPosition(sf::Vector2f(557+325,418));
		window->draw(guiText);
		// hearts
		if (lives>=1)
		{
			heartSprite.setPosition(sf::Vector2f(472+325,420));
			window->draw(heartSprite);
			if(lives>=2)
			{
				heartSprite.setPosition(sf::Vector2f(502+325,420));
				window->draw(heartSprite);
				if(lives==3)
				{
					heartSprite.setPosition(sf::Vector2f(532+325,420));
					window->draw(heartSprite);
				}
			}
		}
		
    }

    //level
	guiText.setString("Level "+std::to_string(level));
	guiText.setCharacterSize(20);
	guiText.setColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(450,380));
	window->draw(guiText);


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

	
}
