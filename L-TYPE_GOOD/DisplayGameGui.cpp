#include "DisplayGameGui.hpp"

void DisplayGameGui::parse_instruction(std::string chaine_instruction){  // A_B_type_x_y&E_H2_valeur&...
	//std::string chaine_instruction(buffer);
	while(chaine_instruction.size() > 1){
		std::size_t idx = chaine_instruction.find(delimiteur_instruction);  //idx du premier delimiteur_instruction (&)
		std::string instruction = chaine_instruction.substr(0,idx);     	// on retire une instruction
		chaine_instruction = chaine_instruction.substr(idx+1,chaine_instruction.size()); // on garde la chaine sans l instruction
		idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l instruction
		std::string type_instruction = instruction.substr(0,idx); 		//on recupère le premier param de l instruction
		instruction = instruction.substr(idx+1,instruction.size()); //on met à jour l'instruction
		if (type_instruction == "A") 		//Affichage
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


int DisplayGameGui::getInputWindow(std::vector<int> *inp){
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
		return 'p';
	}
	return 'v';
	
}
void DisplayGameGui::parse_affichage(std::string instruction){
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
		int explo;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		drawEnemy(x,y,explo, 1);
	}
	else if(objet=="E2"){			//Vaisseau ennemie
		int explo;
		idx = instruction.find(delimiteur_parametre);
		explo = std::stoi(instruction.substr(0,idx));
		drawEnemy(x,y,explo, 2);
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
	else if(objet=="EB") { //Boss
		idx = instruction.find(delimiteur_parametre);
		int bossHp = std::stoi(instruction.substr(0, idx));
		drawBoss(x,y,1, bossHp);
	} 		
	else if(objet=="EB2") {
		idx = instruction.find(delimiteur_parametre);
		int bossHp = std::stoi(instruction.substr(0, idx));
		drawBoss(x,y,2, bossHp);
	} 		
	else if(objet=="B"){		//Bonus
		idx = instruction.find(delimiteur_parametre);
		int type = std::stoi(instruction.substr(0,idx));
		drawBonus(type,x,y);
	}
	else if (objet=="L"){     //level
		idx = instruction.find(delimiteur_parametre);
		int currentLevel = std::stoi(instruction.substr(0,idx));
		drawNewLevel(x,y,currentLevel);
	}


}
void DisplayGameGui::parse_etat(std::string instruction){
	//E_2_HP2_Vies_Score_bonus_level_tick
	size_t idx;
	int player,hp, life, score,level,bonustype;

	idx = instruction.find(delimiteur_parametre); 				//on va voir le premier param de l'instruction
	player = std::stoi(instruction.substr(0,idx)); 		//on recupère le premier param de l'instruction

	instruction = instruction.substr(idx+1,instruction.size()); //on nettoie instruction
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

	drawUi(player,hp, score, life,bonustype,level);
}


void DisplayGameGui::starHandler(){
    //gère le défilement des étoiles en fond
    stars.push_back(new vec2i{static_cast<uint_fast16_t>(rand()) % window->getSize().x, 0});
    for(size_t i = 0; i < stars.size(); i++) {
            stars.at(i)->y += 20;
            if(stars.at(i)->y > 370)
                stars.erase(stars.begin() + static_cast<std::vector<vec2i*>::difference_type>(i));
        }
}


void DisplayGameGui::drawStar() {
    for(auto s : stars){
		sf::CircleShape shape(2.f);
		shape.setPosition(sf::Vector2f(static_cast<float>(s->x), static_cast<float>(s->y)));
		shape.setFillColor(sf::Color::White);
		window->draw(shape);
    }

}


void DisplayGameGui::drawNewLevel(int tick,int levelTick,int currentLevel) {
    if(levelTick != 0 && tick <= levelTick + 600 && tick > levelTick+100){
		guiText.setString("Level " + std::to_string(currentLevel));
		guiText.setFillColor(sf::Color::White);
		guiText.setCharacterSize(22);
		guiText.setPosition(sf::Vector2f(35*12.5, 8*20));
		window->draw(guiText);
    }
}


void DisplayGameGui::initGraphics(){
	window = new sf::RenderWindow(sf::VideoMode(1000, 480), "L-TYPE");

	window->setVerticalSyncEnabled(false);

	// charge les fichiers images et sons
	if (!texture.loadFromFile("imagesAndSounds/healthbar.png"))
	{
		std::cout<<"imagesAndSounds/healthbar.png is missing"<<std::endl;
	}

	if (!heart.loadFromFile("imagesAndSounds/heart.png"))
	{
		std::cout<<"imagesAndSounds/heart.png is missing"<<std::endl;
	}

	if (!font.loadFromFile("imagesAndSounds/space_age.ttf"))
	{
		std::cout<<"imagesAndSounds/space_age.ttf is missing"<<std::endl;
	}

	if (!asteroid.loadFromFile("imagesAndSounds/asteroid.png"))
	{
		std::cout<<"imagesAndSounds/asteroid.png is missing"<<std::endl;
	}

	if (!ship1.loadFromFile("imagesAndSounds/player1.png"))
	{
		std::cout<<"imagesAndSounds/player1.png is missing"<<std::endl;
	}

	if (!ship2.loadFromFile("imagesAndSounds/player2.png"))
	{
		std::cout<<"imagesAndSounds/player2.png is missing"<<std::endl;	}

	if (!laser.loadFromFile("imagesAndSounds/laser.png"))
	{
		std::cout<<"imagesAndSounds/laser.png is missing"<<std::endl;	}

	if (!laser1.loadFromFile("imagesAndSounds/laser1.png"))
	{
		std::cout<<"imagesAndSounds/laser1.png is missing"<<std::endl;	}

	if (!laser2.loadFromFile("imagesAndSounds/laser2.png"))
	{
		std::cout<<"imagesAndSounds/laser2.png is missing"<<std::endl;	}

	if (!tripleshotTex.loadFromFile("imagesAndSounds/tripleshot.png"))
	{
		std::cout<<"imagesAndSounds/tripleshot.png is missing"<<std::endl;	}
	
	if (!damageupTex.loadFromFile("imagesAndSounds/damageup.png"))
	{
		std::cout<<"imagesAndSounds/damageup.png is missing"<<std::endl;	}
	
	if (!lifestealTex.loadFromFile("imagesAndSounds/lifesteal.png"))
	{
		std::cout<<"imagesAndSounds/lifesteal.png is missing"<<std::endl;	}
	
	if (!minigunTex.loadFromFile("imagesAndSounds/minigun.png"))
	{
		std::cout<<"imagesAndSounds/minigun.png is missing"<<std::endl;	}
	if (!enemy.loadFromFile("imagesAndSounds/enemy.png"))
	{
		std::cout<<"imagesAndSounds/enemy.png is missing"<<std::endl;	}

	if (!boss.loadFromFile("imagesAndSounds/boss2.png"))
	{
		std::cout<<"imagesAndSounds/boss2.png is missing"<<std::endl;	}

	if (!enemyH.loadFromFile("imagesAndSounds/enemy2.png"))
	{
		std::cout<<"imagesAndSounds/enemy2.png is missing"<<std::endl;	}

	if (!boss2.loadFromFile("imagesAndSounds/boss.png"))
	{
		std::cout<<"imagesAndSounds/boss.png is missing"<<std::endl;	}

	if (!explosionTex.loadFromFile("imagesAndSounds/explosion_effect.png"))
	{
		std::cout<<"imagesAndSounds/boss2.png is missing"<<std::endl;	}
	
	if (!music.openFromFile("imagesAndSounds/song.ogg"))
		{
		std::cout<<"imagesAndSounds/song.ogg is missing"<<std::endl;
		}
	if (!buffer.loadFromFile("imagesAndSounds/laserSound.wav"))
		{
		std::cout<<"imagesAndSounds/laserSound.wav is missing"<<std::endl;
		}
	if (!buffer1.loadFromFile("imagesAndSounds/explosionSound.wav"))
		{
		std::cout<<"imagesAndSounds/explosionSound.wav is missing"<<std::endl;
		}


	heartSprite.setScale(sf::Vector2f(static_cast<float>(0.03),static_cast<float>(0.03)));
	heartSprite.setTexture(heart);

	health_bar.setScale(sf::Vector2f(static_cast<float>(0.22),static_cast<float>(0.22)));
	health_bar.setTexture(texture);

	health_bar2.setScale(sf::Vector2f(static_cast<float>(0.22),static_cast<float>(0.22)));
	health_bar2.setTexture(texture);

	asteroidSprite.setScale(sf::Vector2f(static_cast<float>(0.14), static_cast<float>(0.16)));
	asteroidSprite.setTexture(asteroid);

	ship1Sprite.setScale(sf::Vector2f(static_cast<float>(0.22),static_cast<float>(0.30)));
	ship1Sprite.setTexture(ship1);

	ship2Sprite.setScale(sf::Vector2f(static_cast<float>(0.22),static_cast<float>(0.30)));
	ship2Sprite.setTexture(ship2);

	laserSprite.setScale(sf::Vector2f(static_cast<float>(0.06),static_cast<float>(0.04)));
	laserSprite.setRotation(1.5);
	laserSprite.setTexture(laser);

	laser1Sprite.setScale(sf::Vector2f(static_cast<float>(0.06),static_cast<float>(0.04)));
	laser1Sprite.setRotation(1.5);
	laser1Sprite.setTexture(laser1);

	laser2Sprite.setScale(sf::Vector2f(static_cast<float>(0.06),static_cast<float>(0.04)));
	laser2Sprite.setRotation(1.5);
	laser2Sprite.setTexture(laser2);

	tripleshotSprite.setScale(sf::Vector2f(static_cast<float>(0.07),static_cast<float>(0.07)));
	tripleshotSprite.setTexture(tripleshotTex);

	damageupSprite.setScale(sf::Vector2f(static_cast<float>(0.07),static_cast<float>(0.07)));
	damageupSprite.setTexture(damageupTex);

	lifestealSprite.setScale(sf::Vector2f(static_cast<float>(0.12),static_cast<float>(0.12)));
	lifestealSprite.setTexture(lifestealTex);

	minigunSprite.setScale(sf::Vector2f(static_cast<float>(0.07),static_cast<float>(0.07)));
	minigunSprite.setTexture(minigunTex);

	enemySprite.setScale(sf::Vector2f(static_cast<float>(0.16),static_cast<float>(0.22)));
	enemySprite.setRotation(180);
	enemySprite.setTexture(enemy);

	bossSprite.setScale(sf::Vector2f(static_cast<float>(0.9),static_cast<float>(0.8)));
	bossSprite.setRotation(180);
	bossSprite.setTexture(boss);

	enemyHSprite.setScale(sf::Vector2f(static_cast<float>(0.16),static_cast<float>(0.22)));
	enemyHSprite.setRotation(180);
	enemyHSprite.setTexture(enemyH);

	boss2Sprite.setScale(sf::Vector2f(static_cast<float>(0.9),static_cast<float>(0.8)));
	boss2Sprite.setRotation(180);
	boss2Sprite.setTexture(boss2);
	
	line.setFillColor(sf::Color::Magenta);
	line.setPosition(sf::Vector2f(static_cast<float>(5),static_cast<float>(370)));

	explosionSprite1.setTexture(explosionTex);
	explosionSprite1.setTextureRect(rectSourceSprite1);

	explosionSprite2.setTexture(explosionTex);
	explosionSprite2.setTextureRect(rectSourceSprite2);

	//sound effects
	laserSound.setBuffer(buffer);
	explosionSound.setBuffer(buffer1);
	//music.setVolume (100.0f);
	music.play();
	music.setLoop(true);
	guiText.setFont(font);

	bossText.setFont(font);
	bossText.setString("BOSS");
	bossText.setPosition(sf::Vector2f(472,425));
	bossText.setCharacterSize(20);

	bossLifeBar.setSize(sf::Vector2f(200, 10));
	bossLifeBar.setFillColor(sf::Color::Red);
	bossLifeBar.setPosition(405,450);

}

void DisplayGameGui::drawObstacle(int x, int y) {
	
	asteroidSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5-4.5),static_cast<float>(y*20)));
	if(y*20 < 350)
		window->draw(asteroidSprite);

}
void DisplayGameGui::drawEnemy(int x, int y, bool isBlinking, int type) {

	if(type == 1){
		if(isBlinking){

			enemySprite.setColor(sf::Color::Red);

		}
		else{
			enemySprite.setColor(sf::Color::White);
		}
		
		enemySprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5+ 60),static_cast<float>(5 + y*20 + 60)));
		if(y*20 < 350){
			window->draw(enemySprite);
		}
	}
	else{
		if(isBlinking){
			enemyHSprite.setColor(sf::Color::Red);
		}
		else{
			enemyHSprite.setColor(sf::Color::White);
		}
		
		enemyHSprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5+ 60), static_cast<float>(5 + y*20 + 60)));
		if(y*20 < 350){
			window->draw(enemyHSprite);
		}
	}
}


void DisplayGameGui::drawProjectile(int x, int y, bool enemy, bool player1){
	if(enemy){
		laserSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5+1), static_cast<float>(y*20+5)));
		window->draw(laserSprite);
	}
	else if (player1) {
		laser1Sprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5+1), static_cast<float>(y*20+5)));
		window->draw(laser1Sprite);
	}
	else{
		laser2Sprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5+1),static_cast<float>(y*20+5)));
		window->draw(laser2Sprite);

	}

}
void DisplayGameGui::drawPlayer(int player, int x , int y, int tick, bool isBlinking){

        if(isBlinking){
			
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
					if (!explo1PosSaved){
						explosionSprite1.setPosition(sf::Vector2f(static_cast<float>(x*12.5-125),static_cast<float>(5 + y*20-110)));
						explo1PosSaved=true;}
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
					if (!explo2PosSaved){
						explosionSprite2.setPosition(sf::Vector2f(static_cast<float>(x*12.5-125),static_cast<float>(5 + y*20-110)));
						explo2PosSaved=true;}
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

		if (player==1 && !isBlinking){
			ship1Sprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5-36.5),static_cast<float>(5 + y*20-55)));
			window->draw(ship1Sprite);
        }
		else if (player==1 && isBlinking && tick % 80 < 40 && exploded1){
			ship1Sprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5-36.5),static_cast<float>(5 + y*20-55)));
			window->draw(ship1Sprite);
		}

        else if (player==2 && !isBlinking){
			ship2Sprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5-36.5),static_cast<float>(5 + y*20-55)));
			window->draw(ship2Sprite);
		}
		else if (player==2 && isBlinking && tick % 80 < 40 && exploded2){
			ship2Sprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5-36.5),static_cast<float>(5 + y*20-55)));
			window->draw(ship2Sprite);
		}
}
void DisplayGameGui::drawBonus(int type, int x, int y){

	if(y*20 < 350){
		if(type==lifeSteal){
			lifestealSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5-11),static_cast<float>(y*20-15)));
			window->draw(lifestealSprite);
		}
		else if(type==minigun){
			minigunSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5-12),static_cast<float>(y*20-15)));
			window->draw(minigunSprite);
		}
		else if(type==damageUp){
			damageupSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5-12),static_cast<float>(y*20-15)));
			window->draw(damageupSprite);
		}
		else if(type==tripleShot){
			tripleshotSprite.setPosition(sf::Vector2f(static_cast<float>((x+1)*12.5-12),static_cast<float>(y*20-15)));
			window->draw(tripleshotSprite);
		}
	}
}

void DisplayGameGui::drawBoss(int x, int y, int type, int bossHp){

		if(type == 1){
			bossSprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5+7 +340),static_cast<float>(5 + y*20 + 260)));
			window->draw(bossSprite);

			bossLifeBar.setSize(sf::Vector2f(200.f/5000.f*static_cast<float>(bossHp), static_cast<float>(10)));
		}else{
			boss2Sprite.setPosition(sf::Vector2f(static_cast<float>(x*12.5+7 +340),static_cast<float>(5 + y*20 + 260)));
			window->draw(boss2Sprite);

			bossLifeBar.setSize(sf::Vector2f(200.f/10000.f*static_cast<float>(bossHp), static_cast<float>(10)));
		}
		window->draw(bossText);
		
		
		window->draw(bossLifeBar);
}
void DisplayGameGui::drawUi(int player, int hp, int score, int lives, int bonusType, int level){

	window->draw(line);
		

	if(player == 0){ 
		//healthbar
		health_bar.setPosition(sf::Vector2f(3,380));
		window->draw(health_bar);
		sf::IntRect rect (0,0,200+((static_cast<int>(texture.getSize().x)-200)/100)*hp,static_cast<int>(texture.getSize().y)); //200=0
		health_bar.setTextureRect(rect);

		//score
		guiText.setString("Score: "+std::to_string(score));
		guiText.setCharacterSize(20);
		guiText.setFillColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(13,440));
		window->draw(guiText);

		//life
		guiText.setString(std::to_string(hp)+"%");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setFillColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(83,386));
		window->draw(guiText);

		//n lives
		guiText.setString("P1");
		guiText.setCharacterSize(19); // exprimée en pixels, pas en points !
		guiText.setFillColor(sf::Color::White);
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
		guiText.setFillColor(sf::Color::White);
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
		sf::IntRect rect (0,0,200+((static_cast<int>(texture.getSize().x)-200)/100)*hp,static_cast<int>(texture.getSize().y)); //200=0
		health_bar2.setTextureRect(rect);

		//score
		guiText.setString("Score: "+std::to_string(score));
		guiText.setCharacterSize(20); // exprimée en pixels, pas en points !
		guiText.setFillColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(470+325,440));
		window->draw(guiText);

		//life
		guiText.setString(std::to_string(hp)+"%");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setFillColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(546+325,386));
		window->draw(guiText);

		//n lives
		guiText.setString("P2");
		guiText.setCharacterSize(18); // exprimée en pixels, pas en points !
		guiText.setFillColor(sf::Color::White);
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
		guiText.setFillColor(sf::Color::White);
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
	if (level < 5) {
		guiText.setString("Level "+std::to_string(level));
		guiText.setCharacterSize(20);
		guiText.setFillColor(sf::Color::White);
		guiText.setPosition(sf::Vector2f(450,380));
		window->draw(guiText);
	}
}


void DisplayGameGui::drawEndGame(std::string score){
	guiText.setString("GAME OVER");
	guiText.setCharacterSize(20);
	guiText.setFillColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(35*12.5, 8*20));
	window->draw(guiText);

	guiText.setString("SCORE : "+score);
	guiText.setPosition(sf::Vector2f(35*12.5, 9*20));
	window->draw(guiText);

	guiText.setString("press p to quit");
	guiText.setFillColor(sf::Color::White);
	guiText.setPosition(sf::Vector2f(32*12.5, 12*20));
	window->draw(guiText);
}
