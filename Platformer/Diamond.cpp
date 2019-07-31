#include "Diamond.h"


Diamond::Diamond(){}

Diamond::Diamond(ResourceHolder* _rh): rh(_rh)
{
	current_sprite.setTexture(rh->diamond.at(anim_index));
	current_sprite.setOrigin(rh->diamond.at(0).getSize().x / 2, (rh->diamond.at(0).getSize().y) / 2);
	current_sprite.setPosition(50, 600);
}


Diamond::~Diamond()
{
}

void Diamond::set_pos(sf::Vector2f pos)
{
	current_sprite.setPosition(pos.x + 32, pos.y + 32);
}

void Diamond::update()
{
	update_tex();
}

void Diamond::update_tex()
{
	
	current_sprite.setTexture(rh->diamond.at(anim_index));
	anim_index++;
	if (anim_index >= 60) anim_index = 0;


}