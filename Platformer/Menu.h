#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
class Screen_1;

class Menu : public sf::RectangleShape
{
public:
	Menu(ResourceHolder* _rh);
	~Menu();

	int choice = 1;
	int min_choice = 1;
	int max_choice = 3;
	void draw(sf::RenderWindow& window);
	void update(char c);
	void do_action(Screen_1& screen);
private:
	ResourceHolder* rh;
	sf::FloatRect menu_rect;
	sf::Text header;
	sf::Text menu1;
	sf::Text menu2;
	sf::Text menu3;
	sf::Text menu4;
	std::vector<std::string> strings =
	{ "Generic Platformer!",
	 "New Game",
	 "Highscores",
	 "Exit" };
	std::vector<sf::Text> texts;
};

