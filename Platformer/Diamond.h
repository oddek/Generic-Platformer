#pragma once
#include "ResourceHolder.h"
class Diamond
{
public:
	Diamond();
	Diamond(ResourceHolder* _rh);
	~Diamond();

	void set_pos(sf::Vector2f pos);
	sf::Sprite current_sprite;
	void update();

private:
	void update_tex();
	ResourceHolder* rh;
	int anim_index = 0;
};

