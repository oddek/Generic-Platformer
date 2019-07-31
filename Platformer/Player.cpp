#include "Player.h"
#include "Screen_1.h"

Player::Player(){}

Player::Player(ResourceHolder* _rh): rh(_rh)
{
	current_sprite.setTexture(rh->player_gun);
	current_sprite.setScale(0.2,0.2);
	current_sprite.setPosition(0, 50);
	
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 15, 36);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}

Player::Player(const Player& p): Player(p.rh){}

Player::~Player()
{
}

void Player::update(Screen_1& screen)
{
	//Let gravity change y_speed
	y_speed += (g*rh->seconds_pr_frame);
	//Make sure sprite direction is correct.
	flip_correct();
	update_current_tiles(screen);
	check_map_collision_x(screen);
	move_x(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
	update_current_tiles(screen);
	check_map_collision_y(screen);
	move_y(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);

	//Check a bunch of stuff if player isnt dead, and level isn't cleared
	if (!killed && !screen.exit && !screen.level_cleared)
	{
		//Update texture to get proper animation
		update_tex();

		check_out_of_bounds(screen);
		check_damage(screen);
		check_crystal(screen);
		check_diamond(screen);
	}
	//Change the sprites for death scene
	if(killed) anim_death();
	
}

void Player::check_out_of_bounds(Screen_1& screen)
{
	auto rect = current_sprite.getGlobalBounds();
	if (rect.top > 20 * 64 || screen.status_bar.time == 0)
	{
		rh->s_fall.play();
		if (screen.status_bar.lives == 0) rh->s_game_over.play();
		screen.set_headline("Death!", 'r', 400);
		killed = true;
		return;
	}
}

void Player::move_x(Screen_1& screen)
{
	//Move map and/or background if necessery
	if (((x_speed > 0 && hitbox.getGlobalBounds().left > rh->view->getCenter().x + 100) || (x_speed < 0 && hitbox.getGlobalBounds().left < rh->view->getCenter().x - 300)))
	{
		rh->view->move(x_speed, 0);
		screen.back_map.move(x_speed*(0.7), 0);
	}
	//Move sprite and update hitbox
	current_sprite.move(x_speed, 0);
}

void Player::move_y(Screen_1& screen)
{
	current_sprite.move(0, y_speed);
}

void Player::check_map_collision_x(Screen_1& screen)
{
	//Get closest obstacle pos x_dir
	if (x_speed > 0)
	{
		for (int i = current_tile_y_top; i <= current_tile_y_bottom; i++)
		{
			if (!screen.check_map_void(current_tile_x_right + 1, i))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_right + 1, i).x - (hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width);
				x_speed = (x_speed <= dist_to_obstacle) ? x_speed : (dist_to_obstacle - 1);
				//if (dist_to_obstacle < 2) x_speed = 0;
				//std::cout << "Dist X: " << dist_to_obstacle << "X_speed: " << x_speed << std::endl;
			}
		}
	}
	//Get closest obstacle neg x_dir;
	else if (x_speed < 0)
	{
		for (int i = current_tile_y_top; i <= current_tile_y_bottom; i++)
		{
			if (!screen.check_map_void(current_tile_x_left - 1, i))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_left + -1, i).x + rh->tile_size - hitbox.getGlobalBounds().left;
				x_speed = (x_speed > dist_to_obstacle) ? x_speed : (dist_to_obstacle + 1);
			}
		}
	}
}

void Player::check_map_collision_y(Screen_1& screen)
{
	//Get closest obstacle pos y_dir;
	if (y_speed > 0)
	{
		for (int i = current_tile_x_left; i <= current_tile_x_right; i++)
		{
			if (!screen.check_map_void(i, current_tile_y_bottom + 1))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_bottom + 1).y - (hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height);
				y_speed = (y_speed < dist_to_obstacle) ? y_speed : (dist_to_obstacle - 1);
				//std::cout << "Dist Y: " << dist_to_obstacle << "Y_speed: " << y_speed << std::endl;
				if (dist_to_obstacle < 2) y_speed = 0;
			}
		}
	}
	//Get closest obstacle neg x_dir
	else if (y_speed < 0)
	{
		for (int i = current_tile_x_left; i <= current_tile_x_right; i++)
		{
			if (!screen.check_map_void(i, current_tile_y_top - 1))
			{
				double dist_to_obstacle = screen.get_cord_of_tile(i, current_tile_y_top - 1).y + rh->tile_size - (hitbox.getGlobalBounds().top);
				y_speed = (y_speed > dist_to_obstacle) ? y_speed : (dist_to_obstacle + 1);
				//std::cout << "Dist Y: " << dist_to_obstacle << "Y_speed: " << y_speed << std::endl;
				//if (dist_to_obstacle < 2) y_speed = 0;
			}
		}
	}
}

//Make sure sprite is facing dir of movement
void Player::flip_correct()
{
	if (x_speed < 0 && !is_flipped)
	{
		is_flipped = !is_flipped;
		auto rect = current_sprite.getTextureRect();
		rect.left = rect.width;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
		current_sprite.move(-hitbox.off_x_l-3, 0);
	}
	else if (x_speed > 0 && is_flipped)
	{
		is_flipped = !is_flipped;
		auto rect = current_sprite.getTextureRect();
		rect.left = 0;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
		current_sprite.move(hitbox.off_x_l+3, 0);
	}
}

void Player::update_tex()
{
	if (killed) return;
	if (shooting)
	{
		current_sprite.setTexture(rh->shooting.at(anim_index));
		anim_index++;
		anim_index %= 11;
		if (anim_index == 10)
		{
			shooting = !shooting;
			anim_index = 0;
		}
	}
	else if (x_speed != 0 && y_speed == 0)
	{
		current_sprite.setTexture(rh->gun_run.at(anim_index));
		anim_index++;
		anim_index %= 10;
	}
	else if (y_speed != 0)
	{
		current_sprite.setTexture(rh->jump_gun);
	}
	else
	{
		current_sprite.setTexture(rh->player_gun);
	}
	current_sprite.setScale(0.2, 0.2);
}

void Player::check_damage(Screen_1& screen)
{
	for (auto& e : screen.enemies)
	{
		if (e->killed) continue;
		if (e->hitbox.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
		{
			rh->s_death.play();
			if (screen.status_bar.lives == 0) rh->s_game_over.play();
			killed = true;
			anim_index = 0;
			y_speed = -10;
			screen.set_headline("Death!", 'r', 400);
			return;
		}
	}
}

void Player::check_crystal(Screen_1& screen)
{
	
	for (auto c = begin(screen.crystals); c != end(screen.crystals);)
	{
		if (c->current_sprite.getGlobalBounds().intersects(hitbox.getGlobalBounds()))
		{
			rh->s_gem.play();
			screen.found_crystals.push_back(c->get_type());
			c = screen.crystals.erase(c);
			screen.status_bar.points += screen.status_bar.crystal_point;
		}
		else c++;
	}
}

void Player::anim_death()
{

	if (anim_count != 0)
	{
		anim_count++;
		if (anim_count >= anim_delay) anim_count = 0;
	}
	else
	{
		current_sprite.setTexture(rh->player_die.at(anim_index));

		anim_count++;
		if(anim_index < rh->player_die.size()-1) anim_index++;
	}
	sf::Vector2i size(rh->player_die[0].getSize().x, rh->player_die[0].getSize().y);
	if(!is_flipped) current_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	else current_sprite.setTextureRect(sf::IntRect(size.x, 0, -size.x, size.y));
}

void Player::check_diamond(Screen_1& screen)
{
	if (hitbox.getGlobalBounds().intersects(screen.diamond.current_sprite.getGlobalBounds())
		&& screen.crystals.empty())
	{
		rh->s_gem.play();
		rh->s_cheer.play();
		screen.level_cleared = true;
		std::string message = (screen.level == screen.no_of_levels - 1) ?
			"Total clearance" : "Level cleared";
		screen.set_headline(message, 'g', 500);
	}
}

void Player::update_current_tiles(Screen_1& screen)
{
	current_tile_x_left = (((hitbox.getGlobalBounds().left) - screen.map.getPosition().x) / rh->tile_size);
	current_tile_x_right = (((hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width) - screen.map.getPosition().x) / rh->tile_size);
	current_tile_y_top = (((hitbox.getGlobalBounds().top) - screen.map.getPosition().y) / rh->tile_size);
	current_tile_y_bottom = (((hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height) - screen.map.getPosition().y) / rh->tile_size);
}

void Player::print_current_tiles()
{
	std::cout << current_tile_x_left << "/" << current_tile_x_right << " - " << current_tile_y_top << "/" << current_tile_y_bottom << '\n';

}