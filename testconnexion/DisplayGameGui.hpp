#ifndef DisplayGameGUI_HPP
#define DisplayGameGUI_HPP
#include <vector>
#include <string>
#include "game_test/Rect.hpp"
#include "game_test/MapHandler.hpp"
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>

class DisplayGameGui
{
	sf::Music music;
	sf::SoundBuffer buffer;
	sf::SoundBuffer buffer1;
	sf::Sound laserSound;
	sf::Sound explosionSound;
	//Game's windows
	sf::RenderWindow* window;
	rect game_area;
    rect screen_area;
	//utilities attribut
	const char delimiteur_instruction = '&';
	const char delimiteur_parametre	  = '_';
	std::vector<vec2i*> stars;
	int tickStar;
	sf::Texture texture;	
	sf::Texture heart;
	sf::Texture asteroid;
	sf::Texture ship1;
	sf::Texture ship2;
	sf::Texture laser;
	sf::Texture laser1;
	sf::Texture laser2;
	sf::Texture tripleshotTex;
	sf::Texture damageupTex;
	sf::Texture lifestealTex;
	sf::Texture minigunTex;
	sf::Texture enemy;
	sf::Texture boss;
	sf::Texture enemyH;
	sf::Texture boss2;
	sf::IntRect rectSourceSprite1{0,0,256,256};
	sf::Sprite explosionSprite1;
	sf::Clock clock1;
	sf::Texture	explosionTex;
	sf::IntRect rectSourceSprite2{0,0,256,256};
	sf::Sprite explosionSprite2;
	sf::Clock clock2;
	bool exploded1=false;
	bool exploded2=false;
	bool explo2PosSaved=false;
	bool explo1PosSaved=false;
	bool twoPlayer=false;
	bool soundExploded1=false;
	bool soundExploded2=false;
	sf::Font font;
	sf::Text guiText;
	sf::Text bossText;
	sf::Sprite heartSprite;
	sf::Sprite health_bar;
	sf::Sprite health_bar2;
	sf::Sprite asteroidSprite;
	sf::Sprite ship1Sprite;
	sf::Sprite ship2Sprite;
	sf::Sprite laserSprite;
	sf::Sprite laser1Sprite;
	sf::Sprite laser2Sprite;
	sf::Sprite tripleshotSprite;
	sf::Sprite damageupSprite;
	sf::Sprite lifestealSprite;
	sf::Sprite minigunSprite;
	sf::Sprite enemySprite;
	sf::Sprite bossSprite;
	sf::Sprite boss2Sprite;
	sf::Sprite enemyHSprite;
	sf::RectangleShape line{sf::Vector2f(990, 2)};
	sf::RectangleShape bossLifeBar;

public:
	//Constructor
	DisplayGameGui()=default;
	void initGraphics();
	//Drawings 
	void drawStar();
	void starHandler();
    void drawObstacle(int x, int y);
    void drawEnemy(int x, int y, int tick, bool isBlinking, int type);
    void drawProjectile(int x, int y, bool enemy, bool player1);
    void drawPlayer(int player, int x , int y, int tick, bool isBlinking);
    void drawBonus(int type, int x, int y);
    void drawBoss(int x, int y, int type, int bossHp);
    void drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick);
	void drawEndGame(std::string score);
	void drawNewLevel(int tick,int levelTick,int currentLevel);
	//...
	int getInputWindow(std::vector<int>* inp);
    
	DisplayGameGui(const DisplayGameGui&)=delete;
	DisplayGameGui& operator=(const DisplayGameGui&)=delete;
	//Destructor
	~DisplayGameGui()=default;
	void close();

	//parsing
	void parse_instruction(std::string);
	// graphics
	bool getIsOpen(){return window->isOpen();}
	sf::RenderWindow* getWindow(){return window;}
private:
	//utilities
	void parse_affichage(std::string instruction);
	void parse_etat(std::string instruction);
};
#endif
