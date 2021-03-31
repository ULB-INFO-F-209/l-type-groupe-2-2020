#ifndef EDITOR_SETTINGS
#define EDITOR_SETTINGS

struct editor_settings{
    int level;

    //enemy
    int enemy_number;
	int enemy_hp;
	int enemy_damage;
	int enemy_speed;

    //bonuses
    int damage_up;
    int triple_shot;
    int life_steal;
    int minigun;

    int drop_rate;

    //obstacle
    int obstacle_number;
	int obstacle_hp;
	int obstacle_damage;
	int obstacle_speed;

    //player 1
    int p1_damage;
    int p1_lives;
    int p1_ship_design;

    //player 2
    int p2_damage;
    int p2_lives;
    int p2_ship_design;

};

#endif // MACRO