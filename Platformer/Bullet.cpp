#include "Bullet.h"



Bullet::Bullet(sf::FloatRect player_rect, bool left_dir, bool up, bool down)
{
	setRadius(5);
	setFillColor(sf::Color::Color::Red);
	setOutlineThickness(2);
	setOutlineColor(sf::Color::Color::Black);

	if (left_dir)
	{
		speed.x = 15;
		setPosition(player_rect.left + 98, player_rect.top + 50);
	}
	else
	{
		speed.x = -15;
		setPosition(player_rect.left, player_rect.top + 50);
	}

	if (up) speed.y = -2;
	else if (down) speed.y = 2;
	else speed.y = 0;
}


Bullet::~Bullet()
{
}

void Bullet::update()
{
	move(speed.x, speed.y);
}
