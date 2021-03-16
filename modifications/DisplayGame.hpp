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
    void drawEnemy(int x, int y);
    void drawProjectile(int x, int y, bool ennemy=true);
    void drawPlayer(int player, int x , int y);
    void drawBonus(int type, int x, int y);
    void drawBoss(int x, int y);
    void drawEtat(int joueur, int hp, int score, int vies);
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
#endif