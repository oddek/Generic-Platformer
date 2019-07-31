#include "Hitbox.h"

Hitbox::Hitbox(){}

Hitbox::Hitbox(int width, int height, int _off_x_l, int _off_x_r): Hitbox(width, height, _off_x_l, _off_x_r, 0, 0)
{
}

Hitbox::Hitbox(int width, int height, int _off_x_l, int _off_x_r, int _off_y_t, int _off_y_b):
	off_x_l(_off_x_l), off_x_r(_off_x_r), off_y_t(_off_y_t), off_y_b(_off_y_b)
{
	setSize(sf::Vector2f(width - off_x_l - off_x_r, height));
	setFillColor(sf::Color::Color::Red);
}


Hitbox::~Hitbox()
{
}

void Hitbox::update_position(sf::FloatRect sprite_rect, bool is_flipped)
{
	sf::Vector2f pos(sprite_rect.left, sprite_rect.top);
	if (is_flipped)
	{
		pos.x += off_x_r;
	}
	else
	{
		pos.x += off_x_l;
	}
	setPosition(pos);
}