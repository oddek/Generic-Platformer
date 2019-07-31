#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include <vector>
class Screen_1;

class Status_bar : public sf::RectangleShape
{
public:
	Status_bar(ResourceHolder* _rh);
	~Status_bar();
	
	ResourceHolder* rh;

	sf::FloatRect bar_rect;
	int time = 200;
	int points = 0;
	int lives = 3;
	int frame_count = 0;
	const int monster_point = 50;
	const int crystal_point = 100;
	const int time_point = 50;
	const int character_size = 20;
	sf::Text time_text;
	sf::Text point_text;
	sf::Text life_text;
	std::vector<sf::Sprite> crystals;


	void update(Screen_1& screen);
	
	void draw(sf::RenderWindow& window);

	sf::Sprite figure;
	
};

