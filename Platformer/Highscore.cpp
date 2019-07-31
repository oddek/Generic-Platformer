#include "Highscore.h"
#include "Screen_1.h"


Highscore::Highscore(ResourceHolder* _rh) : rh(_rh)
{
	load();
	

	setSize(sf::Vector2f(rh->s_width, rh->s_height));
	setFillColor(sf::Color(0x00000088));
	rect = getGlobalBounds();
	sf::Vector2f pos(rect.left + rect.width / 2, 300);
	for (int i = 0; i < 4; i++)
	{
		sf::Text t;
		t.setFont(rh->font1);
		t.setCharacterSize((i == 0) ? 80 : 50);
		t.setOutlineThickness(5);
		t.setFillColor(sf::Color(255, 255, 255, 255));
		t.setOutlineColor(sf::Color(0x000000FF));
		t.setStyle(sf::Text::Bold);
		auto rect = t.getGlobalBounds();
		t.setOrigin(rect.width / 2, rect.height / 2);
		t.setPosition(pos);

		texts.push_back(t);
		pos.y += (i == 0) ? 200 : 100;
	}
	texts[0].setString("Highscores");
	texts[1].setString(std::to_string(highscore) + "p");
	texts[2].setString(std::to_string(record_time / 60) + ":" + 
		((record_time % 60 < 10) ? "0" : "") + std::to_string(record_time % 60));
	texts[3].setString("Exit");
	texts[3].setFillColor(sf::Color(0x009a00FF));
}


Highscore::~Highscore()
{
}

void Highscore::load()
{
	std::ifstream ist("highscore.txt");
	ist >> highscore;
	ist >> record_time;
	ist.close();

	minutes = record_time / 60;
	seconds = record_time % 60;
}

void Highscore::save(int score, int seconds)
{
	std::ofstream ost("highscore.txt");
	ost << ((highscore < score) ? score : highscore);
	ost << std::endl;
	ost << ((record_time < seconds) ? record_time : seconds);
	ost.close();
	load();
}

void Highscore::draw(sf::RenderWindow& window)
{
	texts[0].setString("Highscores");
	texts[1].setString(std::to_string(highscore) + "p");
	texts[2].setString(std::to_string(record_time / 60) + ":" +
		((record_time % 60 < 10) ? "0" : "") + std::to_string(record_time % 60));
	
	

	window.draw(*this);
	sf::Vector2f pos(rect.left + rect.width / 2, 300);
	for (auto t = texts.begin(); t != texts.end();)
	{
		auto rect = t->getGlobalBounds();
		t->setOrigin(rect.width / 2, rect.height / 2);
		t->setPosition(pos);

		window.draw(*t);

		pos.y += (t == texts.begin()) ? 200 : 100;
		t++;
	}
}