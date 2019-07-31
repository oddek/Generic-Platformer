#include "Crystal.h"


int Crystal::count = 0;

Crystal::Crystal(){}

Crystal::Crystal(ResourceHolder* _rh, sf::Vector2f pos): rh(_rh)
{
	current_sprite.setTexture(rh->crystals.at(count));
	current_sprite.setTextureRect(sf::IntRect(0, 0, rh->crystals.at(0).getSize().x / no_of_tiles, rh->crystals.at(0).getSize().y));
	current_sprite.setOrigin((rh->crystals.at(0).getSize().x / no_of_tiles) / 2, (rh->crystals.at(0).getSize().y) / 2);
	current_sprite.setPosition(pos.x+32, pos.y+32);
	type = count;
	count++;
}


Crystal::~Crystal()
{
}

void Crystal::update()
{
	update_tex();
}

void Crystal::update_tex()
{
	if (current_anim_delay >= anim_delay)
	{
		current_sprite.setTextureRect(sf::IntRect(current_anim_index *(rh->crystals.at(0).getSize().x / no_of_tiles), 0, rh->crystals.at(0).getSize().x / no_of_tiles, rh->crystals.at(0).getSize().y));
		current_anim_index++;
		if (current_anim_index >= no_of_tiles) current_anim_index = 0;
		current_anim_delay = 0;
	}
	else current_anim_delay++;
}

void Crystal::reset_statics()
{
	count = 0;
}