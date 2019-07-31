#include "Devil.h"



Devil::Devil(ResourceHolder* _rh, sf::Vector2f pos): Enemy(_rh, pos)
{
	current_sprite.setTexture(rh->enemy1_idle[0]);
	x_speed = 2;
	hitbox = Hitbox(current_sprite.getGlobalBounds().width, current_sprite.getGlobalBounds().height, 5, 5);

	hitbox.update_position(current_sprite.getGlobalBounds(), is_flipped);
}

Devil::~Devil()
{
}

void Devil::update_tex()
{
	if (killed) current_sprite.setTexture(rh->enemy1_hit);
	else
	{
		anim_counter++;
		if (anim_counter > max_anim_delay)
		{
			current_sprite.setTexture(rh->enemy1_idle[anim_index]);
			anim_index++;
			anim_index %= 2;
			anim_counter = 0;
		}
	}
}