#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"


class Crystal
{
public:
	Crystal();
	Crystal(ResourceHolder* _rh, sf::Vector2f pos);
	~Crystal();

	sf::Sprite current_sprite;
	void update();
	void reset_statics();
	int get_type() { return type; }
private:
	static int count;
	int type;
	static const int no_of_tiles = 8;
	static const int anim_delay = 4;;
	int current_anim_index = 0;
	int current_anim_delay = 0;
	
	void update_tex();
	ResourceHolder* rh;
};

