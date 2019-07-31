#include "Screen_1.h"



Screen_1::Screen_1(ResourceHolder* _rh) : rh(_rh), player(_rh), status_bar(_rh), menu(_rh), highscore(_rh), diamond(_rh)
{
	init_level();
	init_background();
}

void Screen_1::reset()
{
	level_cleared = false;
	game_over_delay = 120;
	status_bar.time = 200;

	player = Player(rh);
	player.update(*this);

	Crystal c;
	c.reset_statics();
	found_crystals.clear();
	
	init_level();
	init_background();

	if(level == 0) rh->view->setCenter(rh->s_width / 2, rh->s_height / 2);
	else rh->view->setCenter(player.current_sprite.getGlobalBounds().left, rh->s_height / 2);
	 

	set_headline("Start!", 'g', 120);
}

Screen_1::~Screen_1()
{
}

int Screen_1::Run(sf::RenderWindow& window)
{
	bool pause = false;
	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//draw_header_count = 0;
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					if(show_menu) show_menu = false;
					else if (show_scores)
					{
						show_scores = false;
						show_menu = true;
					}
					else show_menu = true;
					break;
				case sf::Keyboard::Up:
				{
					if (show_menu)
						menu.update('u');
					break;
				}
				case sf::Keyboard::Down:
					if (show_menu)
						menu.update('d');
					break;
				case sf::Keyboard::Enter:
					if (show_menu)
						menu.do_action(*this);
					else if (show_scores)
					{
						show_scores = false;
						show_menu = true;
					}
					break;
				case sf::Keyboard::Right:
					if (show_menu || show_scores) break;
					t1 = std::chrono::high_resolution_clock::now();
					move_left = false;
					move_right = true;
					//player.x_speed = 10;
					break;
				case sf::Keyboard::Left:
					if (show_menu || show_scores) break;
					t1 = std::chrono::high_resolution_clock::now();
					move_right = false;
					move_left = true;
					//player.x_speed = -10;
					break;
				case sf::Keyboard::F:
					if (show_menu || show_scores) break;
					if (player.y_speed == 0)
					{
						rh->s_jump.play();
						player.y_speed = -25;
					}	
					break;
				case sf::Keyboard::P:
					if (show_menu || show_scores) break;
					pause = !pause;
					break;
				case sf::Keyboard::D:
					if (show_menu || show_scores) break;
					shot_fired(false, false);
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					move_right = false;
					//player.x_speed = 0;
					break;
				case sf::Keyboard::Left:
					move_left = false;
					//player.x_speed = 0;
					break;
				}
			}
		}
		
		if (exit)
		{
			return 0;
		}
		if (player.killed)
		{
			move_left = false;
			move_right = false;
			
			if (game_over_delay == 0)
			{
				std::cout << "Ferdig!" << std::endl;
				status_bar.lives--;
				Crystal c;
				c.reset_statics();
				if (status_bar.lives < 0)
				{
					highscore.save(status_bar.points, 1000000);
					return 2;
				}
				reset();
			}
			if(game_over_delay > 0) game_over_delay--;
			std::cout << game_over_delay << std::endl;
			

		}
		if (level_cleared)
		{
			move_left = false;
			move_right = false;
			
			if (game_over_delay == 0 && status_bar.time == 0)
			{
				if(level < no_of_levels-1) level++;
				else
				{
					Crystal c;
					c.reset_statics();
					end_master = std::chrono::high_resolution_clock::now();
					auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end_master - master_clock);
					highscore.save(status_bar.points, seconds.count());
					return 2;
				}
				reset();
			}
			if(game_over_delay > 0) game_over_delay--;
			
		}
		if (move_left)
		{
			player.x_speed = -10;
		}
		else if (move_right)
		{
			player.x_speed = 10;
		}
		else player.x_speed = 0;

		t4 = std::chrono::high_resolution_clock::now();
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3);
		if (milliseconds.count() > millis_pr_frame)
		{
			if (!pause)
			{
				
				if(!show_menu && !show_scores) player.update(*this);
				for (auto& i : enemies) i->update(*this);
				for (auto& i : bullets) i.update();
				for (auto& i : crystals) i.update();
				diamond.update();
				rh->back_sprite.setPosition(rh->view->getCenter().x - rh->view->getSize().x, 0);
				check_bullet_out_of_view(window);
				check_bullet_hit_enemy();
				delete_enemies();
				status_bar.update(*this);
				if (draw_header_count > 0) draw_header_count--;
			}
			t3 = std::chrono::high_resolution_clock::now();

		}
		
		
		window.clear();
		window.setView(*rh->view);
		window.draw(rh->back_sprite);
		window.draw(back_map);
		window.draw(map);
		for (auto i : crystals) window.draw(i.current_sprite);
		window.draw(diamond.current_sprite);
		if(!show_menu && !show_scores) window.draw(player.current_sprite);
		for (const auto& i : enemies)
		{
			window.draw(i->current_sprite);
			//window.draw(i.hitbox);
		}
		for (auto i : bullets) window.draw(i);

		if (draw_header_count != 0) window.draw(headline);
		//window.draw(player.hitbox);
		
		if (show_menu)
		{
			window.setView(*rh->menu_view);
			menu.draw(window);
		}
		else if (show_scores)
		{
			window.setView(*rh->menu_view);
			highscore.draw(window);
		}
		else
		{
			window.setView(*rh->stat_view);
			status_bar.draw(window);
		}
		
		window.display();
	}
}

void Screen_1::init_background()
{
	int id = -1; 
	current_background.clear();
	
	for (int i = 0; i < rh->map_back.getSize().y; i++)
	{
		for (int j = 0; j < rh->map_back.getSize().x; j++)
		{
			sf::Color c = rh->map_back.getPixel(j, i);

			if (c == sf::Color(0x7F0037FF))
			{
				id = 37;
			}
			else if (c == sf::Color(0xFF006EFF))
			{
				id = 38;
			}
			else { id = -1; }

			current_background.push_back(id);
		}
	}
	back_map.load("img/Tiles_64x64.png", sf::Vector2u(rh->tile_size, rh->tile_size), current_background, rh->map_back.getSize().x, rh->map_back.getSize().y);
	back_map.setPosition(-1000, 0);
}

void Screen_1::init_level()
{
	int id = 0;
	current_level.clear();
	crystals.clear();
	enemies.clear();

	std::cout << "Kom hit" << std::endl;
	for (int i = 0; i < rh->maps[level].getSize().y; i++)
	{
		for (int j = 0; j < rh->maps[level].getSize().x; j++)
		{
			sf::Color c = rh->maps[level].getPixel(j, i);

			if (c == sf::Color(0xFF0000FF))
			{
				id = 4;
			}
			else if (c == sf::Color(0x4CFF00FF))
			{
				id = 0;
			}
			else if (c == sf::Color(0x0026FFFF))
			{
				id = 11;
			}
			else if (c == sf::Color(0x7F6A00FF))
			{
				id = -1;
				enemies.emplace_back(std::make_unique<Devil>(rh, get_cord_of_tile(j, i)));
				
				//e.update(*this);
				
			}
			else if (c == sf::Color(0x0094FFFF))
			{
				id = -1;
				enemies.emplace_back(std::make_unique<Bird>(rh, get_cord_of_tile(j, i), sf::Vector2i(j, i)));
			}
			else if (c == sf::Color(0x00FFFFFF))
			{
				id = -1;
				Crystal c(rh, get_cord_of_tile(j, i));
				crystals.push_back(c);
			}
			else if (c == sf::Color(0xFF6A00FF))
			{
				id = -1;
				diamond.set_pos(get_cord_of_tile(j, i));
			}
			else if (c == sf::Color(0x7F006EFF))
			{
				id = 51;
			}
			else if (c == sf::Color(0x267F00FF))
			{
				id = 23;
			}
			/*else if (c == sf::Color(0x000000FF))
			{
				//id = -1;
				//player.current_sprite.setPosition(get_cord_of_tile(j, i));
				//player.update(*this);
			}*/
			else { id = -1; }

			current_level.push_back(id);
		}
	}
	map.load("img/Tiles_64x64.png", sf::Vector2u(rh->tile_size, rh->tile_size), current_level, rh->maps[level].getSize().x, rh->maps[level].getSize().y);
}

bool Screen_1::check_map_void(int x, int y)
{
	if (x < 0 || x >= map.m_width || y < 0 || y >= map.m_height) return true;

	return (current_level.at(y*map.m_width + x) == -1);
}

sf::Vector2f Screen_1::get_cord_of_tile(int x, int y)
{
	return sf::Vector2f((x * rh->tile_size) + map.getPosition().x, y*rh->tile_size + map.getPosition().y);
}

void Screen_1::shot_fired(bool up, bool down)
{
	if (!player.gun) return;
	rh->s_shot.play();
	player.shooting = true;
	player.anim_index = 0;
	auto playerRect = player.current_sprite.getGlobalBounds();
	Bullet b(player.current_sprite.getGlobalBounds(), !player.is_flipped, up, down);
	bullets.push_back(b);

}

void Screen_1::check_bullet_hit_enemy()
{
	for (auto b = begin(bullets); b != end(bullets);)
	{
		for (auto e = begin(enemies); e != end(enemies);)
		{
			if (b->getGlobalBounds().intersects((*e)->hitbox.getGlobalBounds()) && !(*e)->killed)
			{
				rh->s_monster_death.play();
				(*e)->y_speed = - 10;
				if ((b->speed.x < 0 && (*e)->x_speed > 0) || b->speed.x > 0 && (*e)->x_speed < 0) (*e)->x_speed *= -1;
				(*e)->killed = true;

				b = bullets.erase(b);
				status_bar.points += status_bar.monster_point;
				if (b == end(bullets)) return;
			}
			e++;
			




			//Funker men vil legge inn anim
			/*if (b->getGlobalBounds().intersects(e->hitbox.getGlobalBounds()))
			{
				rh->s_monster_death.play();
				e = enemies.erase(e);
				b = bullets.erase(b);
				status_bar.points += status_bar.monster_point;
				if(b == end(bullets)) return;
			}
			else
			{
				e++;
			}*/
		}
		b++;
	}
}

void Screen_1::delete_enemies()
{
	for (auto e = enemies.begin(); e != enemies.end();)
	{
		if ((*e)->y_speed == 0 && (*e)->killed) e = enemies.erase(e);
		else e++;
	}
}

void Screen_1::check_bullet_out_of_view(sf::RenderWindow& window)
{
	
	for (auto b = begin(bullets); b != end(bullets);)
	{
		auto b_pos = window.mapCoordsToPixel(b->getPosition(), *rh->view);
		if (b_pos.x < 0 || b_pos.x > rh->s_width)
		{
			b = bullets.erase(b);
		}
		else
		{
			b++;
		}
	}
	
}


void Screen_1::set_headline(std::string str, char color, int length)
{
	switch (color)
	{
	case 'g':
		headline.setFillColor(sf::Color(0x009a00FF));
		break;
	case 'r':
		headline.setFillColor(sf::Color(0xdb1111FF));
		break;
	}
	headline.setOutlineColor(sf::Color(0x000000FF));
	headline.setOutlineThickness(10);
	headline.setStyle(sf::Text::Bold);
	headline.setString(str);
	auto text_rect = headline.getGlobalBounds();
	headline.setOrigin(text_rect.width / 2, text_rect.height / 2);
	headline.setPosition(rh->view->getCenter());

	draw_header_count = length;
}

