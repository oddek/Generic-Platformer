#pragma once
#include "Enemy.h"

class Devil : public Enemy
{
public:
	Devil(ResourceHolder* _rh, sf::Vector2f pos);
	~Devil();
	const int type = 0;
	void update_tex();
};

