#ifndef DisplayGame_HPP
#define DisplayGame_HPP
#include <ncurses.h>
#include <vector>
#include <string>
#include "game_test/Rect.hpp"
#include "game_test/MapHandler.hpp"
#include <unistd.h>
#include <SFML/Graphics.hpp>


class DisplayGame
{
	//Game's windows
	sf::RenderWindow* window;
	WINDOW* main_wnd;
    WINDOW* game_wnd;
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


	sf::Font font;
	sf::Text guiText;
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
	sf::RectangleShape line{sf::Vector2f(990, 2)};

public:
	//Constructor
	DisplayGame()=default;
	int init();
	void initGraphics();
	//Drawings 
	void drawStar();
	void starHandler();
    void drawObstacle(int x, int y);
    void drawEnemy(int x, int y, int tick, bool isBlinking);
    void drawProjectile(int x, int y, bool enemy, bool player1);
    void drawPlayer(int player, int x , int y, int tick, bool isBlinking);
    void drawBonus(int type, int x, int y);
    void drawBoss(int x, int y);
    void drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick);
	void drawEnergyBar(int a);
	void drawEndGame(std::string score);
	void drawNewLevel(int tick,int levelTick,int currentLevel);
	//...
	int getInputWindow();
	int inline getInput(){return wgetch(main_wnd);}
    
	//Destructor
	~DisplayGame()=default;
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
	void refreshWnd();
	void eraseWnd();


};
#endif