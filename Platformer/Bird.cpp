#include "Bird.h"
#include "Screen_1.h"


/*
La de snu etter pos.x +- 10 ||
Krasher i pos.x.
Hvis krasj i y retning, sett y_speed  = 0, den vil øke eller synke neste iterasjon.

*/

Bird::Bird(ResourceHolder* _rh, sf::Vector2f pos, sf::Vector2i _init_pos): Enemy(_rh, pos), init_pos(_init_pos)
{
	current_sprite.setTexture(rh->enemy2[0]);
	x_speed = 2;
	y_speed = 0.5;
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 14, 5, 11, 9);

	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}


Bird::~Bird()
{
}


void Bird::update(Screen_1& screen)
{
	//Let gravity change y_speed
	if(killed) y_speed += (g*rh->seconds_pr_frame);
	//Make sure sprite direction is correct.
	if (!killed) flip_correct();
	//Get current_tile
	update_current_tiles(screen);
	if (!killed) check_map_collision_x(screen);
	move_x(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
	update_current_tiles(screen);
	if(!killed)check_map_collision_y(screen);
	move_y(screen);
	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);

	update_tex();
}

void Bird::update_tex()
{
	if (killed) current_sprite.setRotation(90);
	else
	{
		anim_counter++;
		if (anim_counter > max_anim_delay)
		{
			current_sprite.setTexture(rh->enemy2[anim_index]);
			anim_index++;
			anim_index %= 4;
			anim_counter = 0;
		}
	}
}

void Bird::flip_correct()
{
	if (x_speed < 0 && is_flipped)
	{
		is_flipped = !is_flipped;
		auto rect = current_sprite.getTextureRect();
		rect.left = rect.width;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
	else if (x_speed > 0 && !is_flipped)
	{
		is_flipped = !is_flipped;

		auto rect = current_sprite.getTextureRect();
		rect.left = 0;
		rect.width = -rect.width;
		current_sprite.setTextureRect(rect);
	}
}

void Bird::check_map_collision_x(Screen_1& screen)
{
	//Get closest obstacle pos x_dir
	if (x_speed > 0)
	{
		if (!screen.check_map_void(current_tile_x_right, current_tile_y_bottom) ||
			current_tile_x_right - init_pos.x >= limits.x)
		{
			x_speed *= -1;
		}
	}
	//Get closest obstacle neg x_dir;
	else if (x_speed < 0)
	{
		if (!screen.check_map_void(current_tile_x_left, current_tile_y_bottom) ||
			abs(current_tile_x_left - init_pos.x) >= limits.x)
		{
			x_speed *= -1;
		}
	}
}

void Bird::check_map_collision_y(Screen_1& screen)
{
	//Get closest obstacle pos y_dir;
	if (y_speed > 0)
	{
		
		if (!screen.check_map_void(current_tile_x_right, current_tile_y_bottom) ||
			abs(current_tile_y_bottom - init_pos.y) >= limits.y)
		{
			//double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_right, current_tile_y_bottom + 1).y - (hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height);
			//y_speed = (y_speed < dist_to_obstacle) ? y_speed : (dist_to_obstacle - 1);
			//std::cout << "Dist Y: " << dist_to_obstacle << "Y_speed: " << y_speed << std::endl;
			y_speed *= -1;
		}
	}
	//Get closest obstacle neg x_dir
	else if (y_speed < 0)
	{
		if (!screen.check_map_void(current_tile_x_left, current_tile_y_top) ||
			abs(current_tile_y_top - init_pos.y) >= limits.y)
		{
			//double dist_to_obstacle = screen.get_cord_of_tile(current_tile_x_left, current_tile_y_top - 1).y + rh->tile_size - (hitbox.getGlobalBounds().top);
			
			//std::cout << "Dist Y: " << dist_to_obstacle << "Y_speed: " << y_speed << std::endl;
			y_speed *= -1;
		}
	}
}