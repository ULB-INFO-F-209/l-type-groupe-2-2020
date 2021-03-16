#ifndef DisplayGame_HPP
#define DisplayGame_HPP
#include <ncurses.h>
#include <vector>
#include <string>
#include "Rect.hpp"
class DisplayGame
{
	//Game's windows
	WINDOW* main_wnd;
    WINDOW* game_wnd;
	rect game_area;
    rect screen_area;
	//utilities attribut
	constexpr char delimiteur_instruction = '&';
	constexpr char delimiteur_parametre	  = '_';
	std::vector<vec2i*> stars;
public:
	//Constructor
	DisplayGame()=default;
	int init();
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
    //...
    
	//Destructor
	~DisplayGame()=default;

	//parsing
	void parse_instruction(char *buffer);

private:
	//utilities
	void parse_affichage(std::string instruction);
	void parse_etat(std::string instruction);
};
enum bonusType{damageUp, tripleShot, lifeSteal, minigun, noBonus};
#endif