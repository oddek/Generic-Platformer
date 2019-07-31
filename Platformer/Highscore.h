#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "ResourceHolder.h"
class Highscore : public sf::RectangleShape
{
public:
	Highscore(ResourceHolder* _rh);
	~Highscore();
	ResourceHolder* rh;
	void load();
	void save(int score, int seconds);
	void draw(sf::RenderWindow& window);

	int highscore;
	int record_time;
	int minutes;
	int seconds;
	sf::FloatRect rect;
	std::vector<std::string> strings;
	std::vector<sf::Text> texts;
};

