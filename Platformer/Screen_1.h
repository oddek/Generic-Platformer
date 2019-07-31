#pragma once
#include "cScreen.h"
#include "Map.h"
#include <chrono>
#include <fstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Crystal.h"
#include "Diamond.h"
#include "Status_bar.h"
#include "Menu.h"
#include "Highscore.h"
#include "Devil.h"
#include "Bird.h"

class Screen_1 : public cScreen
{
public:
	Screen_1(ResourceHolder* _rh);
	~Screen_1();
	bool show_menu = true;
	bool show_scores = false;
	bool level_cleared = false;
	bool exit = false;

	int level = 0;
	int no_of_levels = 3;
	int game_over_delay = 120;
	
	ResourceHolder* rh;
	Status_bar status_bar;
	Menu menu;
	Highscore highscore;
	Player player;
	Map map;
	Map back_map;
	Diamond diamond;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<Bullet> bullets;
	std::vector<Crystal> crystals;
	std::vector<int> found_crystals;
	std::vector<int> current_level;
	std::vector<int> current_background;

	std::chrono::time_point<std::chrono::high_resolution_clock> master_clock = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> end_master = std::chrono::high_resolution_clock::now();

	int Run(sf::RenderWindow& window);
	bool check_map_void(int x, int y);
	sf::Vector2f get_cord_of_tile(int x, int y);
	void reset();
	void set_headline(std::string str, char color, int length);

private:
	int millis_pr_frame = 17;
	bool move_left = false;
	bool move_right = false;
	int draw_header_count = 0;
	sf::Text headline;

	void check_bullet_hit_enemy();
	void check_bullet_out_of_view(sf::RenderWindow& window);
	void init_level();
	void init_background();
	void shot_fired(bool up, bool down);
	void delete_enemies();
	std::chrono::time_point<std::chrono::high_resolution_clock> t1 = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> t2 = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> t3 = std::chrono::high_resolution_clock::now();
	std::chrono::time_point<std::chrono::high_resolution_clock> t4 = std::chrono::high_resolution_clock::now();
};

