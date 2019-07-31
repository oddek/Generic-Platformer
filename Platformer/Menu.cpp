#include "Menu.h"
#include "Screen_1.h"


Menu::Menu(ResourceHolder* _rh): rh(_rh)
{
	setSize(sf::Vector2f(rh->s_width, rh->s_height));
	setFillColor(sf::Color(0x00000088));
	menu_rect = getGlobalBounds();
	sf::Vector2f pos(menu_rect.left + menu_rect.width / 2, 300);
	for (int i = 0; i < strings.size(); i++)
	{
		sf::Text t;
		t.setFont(rh->font1);
		t.setCharacterSize((i == 0) ? 80 : 50);
		t.setOutlineThickness(5);
		
		t.setFillColor((i == choice) ? sf::Color(0x009a00FF) : sf::Color(255, 255, 255, 255));
		
		t.setOutlineColor(sf::Color(0x000000FF));
		t.setString(strings[i]);
		t.setStyle(sf::Text::Bold);
		auto rect = t.getGlobalBounds();
		t.setOrigin(rect.width / 2, rect.height / 2);
		t.setPosition(pos);

		texts.push_back(t);
		pos.y += (i == 0) ? 200 : 100;
	}
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	for (auto i : texts) window.draw(i);
}

void Menu::update(char c)
{
	switch (c)
	{
	case 'u':
		if (choice > min_choice) choice--;
		break;
	case 'd':
		if (choice < max_choice) choice++;
		break;
	}

	for (int i = 0; i < texts.size(); i++)
	{
		texts[i].setFillColor((i == choice) ? sf::Color(0x009a00FF) : sf::Color(255, 255, 255, 255));
	}
}

void Menu::do_action(Screen_1& screen)
{
	switch (choice)
	{
	case 1:
		screen.show_menu = false;
		screen.level = 2;
		screen.reset();
		screen.master_clock = std::chrono::high_resolution_clock::now();
		break;
	case 2:
		screen.show_menu = false;
		screen.show_scores = true;
		break;
	case 3:
		screen.exit = true;
		break;
	}
}


