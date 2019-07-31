#pragma once
#include <SFML/Graphics.hpp>
class Bullet : public sf::CircleShape
{
public:
	Bullet(sf::FloatRect player_rect, bool left_dir, bool up, bool down);
	~Bullet();

	sf::Vector2f speed;
	void update();
};

