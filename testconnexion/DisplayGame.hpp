#ifndef DisplayGame_HPP
#define DisplayGame_HPP
#include <ncurses.h>
#include <vector>
#include <string>
#include "game_test/Rect.hpp"
#include "game_test/MapHandler.hpp"
#include <unistd.h>

class DisplayGame
{
	//Game's windows
	WINDOW* main_wnd;
    WINDOW* game_wnd;
	rect game_area;
    rect screen_area;
	//utilities attribut
	const char delimiteur_instruction = '&';
	const char delimiteur_parametre	  = '_';
	std::vector<vec2i*> stars;
	int tickStar;
public:
	//Constructor
	DisplayGame()=default;
	int init();
	//Drawings 
	void drawStar();
	void starHandler();
    void drawObstacle(int x, int y);
    void drawEnemy(int x, int y, bool isBlinking, int type);
    void drawProjectile(int x, int y, bool enemy, bool player1);
    void drawPlayer(int player, int x , int y, int tick, bool isBlinking);
    void drawBonus(int type, int x, int y);
    void drawBoss(int x, int y, int type);
    void drawUi(int player, int hp, int score, int lives, int bonusType, int level, int tick);
	void drawEnergyBar(int a);
	void drawEndGame(std::string score);
	void drawNewLevel(int tick,int levelTick,int currentLevel);
	//...
	int inline getInput(){return wgetch(main_wnd);}
    
	//Destructor
	~DisplayGame()=default;
	void close();

	DisplayGame(const DisplayGame&)=delete;
	DisplayGame& operator=(const DisplayGame&)=delete;

	//parsing
	void parse_instruction(std::string);

private:
	//utilities
	void parse_affichage(std::string instruction);
	void parse_etat(std::string instruction);
	void refreshWnd();
	void eraseWnd();


};
#endif