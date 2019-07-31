#include "Status_bar.h"
#include "Screen_1.h"


Status_bar::Status_bar(ResourceHolder* _rh): rh(_rh)
{
	//Setup the status rect
	setSize(sf::Vector2f(rh->s_width, 100));
	setFillColor(sf::Color(0x00000055));
	bar_rect = getGlobalBounds();
	//Setup lifefigure
	figure.setTexture(rh->player_gun);
	figure.setScale(0.2, 0.2);
	auto figure_rect = figure.getGlobalBounds();
	//figure.setOrigin(figure_rect.width / 2, figure_rect.height / 2);
	//figure.setPosition(bar_rect.left + 60, bar_rect.top + bar_rect.height / 2);
	figure.setPosition(10, 10);
	//Setup lifetext
	life_text.setFont(rh->font1);
	life_text.setCharacterSize(character_size);
	life_text.setString("X " + std::to_string(lives));
	sf::FloatRect life_rect = life_text.getGlobalBounds();
	life_text.setOrigin(life_rect.width / 2, life_rect.height / 2);
	life_text.setPosition(120, bar_rect.top + bar_rect.height / 2);
	//Setup timetext
	time_text.setFont(rh->font1);
	time_text.setCharacterSize(character_size);
	time_text.setString("Time: " + std::to_string(time));
	sf::FloatRect time_rect = time_text.getGlobalBounds();
	time_text.setOrigin(time_rect.width / 2, time_rect.height / 2);
	time_text.setPosition(bar_rect.left + bar_rect.width * 3 / 4, bar_rect.top + bar_rect.height/2);
	//Setup point text
	point_text.setFont(rh->font1);
	point_text.setCharacterSize(character_size);
	point_text.setString("Points: " + std::to_string(points));
	sf::FloatRect point_rect = point_text.getGlobalBounds();
	point_text.setOrigin(point_rect.width / 2, point_rect.height / 2);
	point_text.setPosition(bar_rect.left + bar_rect.width / 4, bar_rect.top + bar_rect.height / 2);
	//Setup crystal_img
	sf::Vector2f pos(680, bar_rect.height / 2);
	for (int i = 0; i < rh->crystals.size(); i++)
	{
		sf::Sprite s;
		s.setTexture(rh->crystals.at(i));
		s.setTextureRect(sf::IntRect(0, 0, rh->crystals.at(i).getSize().x / 8, rh->crystals.at(i).getSize().y));
		s.setOrigin((rh->crystals.at(0).getSize().x / 8) / 2, (rh->crystals.at(0).getSize().y) / 2);
		s.setPosition(pos);
		s.setColor(sf::Color(0xFFFFFF22));
		crystals.push_back(s);
		
		pos.x += 40;
	}
}


Status_bar::~Status_bar()
{
}


void Status_bar::update(Screen_1& screen)
{
	if (screen.level_cleared)
	{
		points += time_point;
		time--;
		time_text.setString("Time: " + std::to_string(time));
	}
	life_text.setString("X " + std::to_string(lives));
	point_text.setString("Points: " + std::to_string(points));
	frame_count++;
	if (frame_count >= 60)
	{
		time_text.setString("Time: " + std::to_string(time));
		time--;
		frame_count = 0;
	}

	for (int i = 0; i < screen.found_crystals.size(); i++)
	{
		crystals[screen.found_crystals[i]].setColor(sf::Color(0xFFFFFFFF));
	}
	if (screen.found_crystals.empty())
	{
		for (auto& i : crystals) i.setColor(sf::Color(0xFFFFFF22));
	}
	
}

void Status_bar::draw(sf::RenderWindow& window)
{
	window.draw(*this);
	window.draw(figure);
	window.draw(life_text);
	window.draw(time_text);
	window.draw(point_text);
	for (auto& i : crystals) window.draw(i);
}