#pragma once
#include "Enemy.h"

class Bird : public Enemy
{
public:
	Bird(ResourceHolder* _rh, sf::Vector2f pos, sf::Vector2i init_pos);
	~Bird();
	const int type = 1;
	void update_tex();
	void update(Screen_1& screen);
	void flip_correct();
	void check_map_collision_y(Screen_1& screen);
	void check_map_collision_x(Screen_1& screen);

	sf::Vector2i init_pos;
	sf::Vector2i limits = sf::Vector2i(5, 1);
};

