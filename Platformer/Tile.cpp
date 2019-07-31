#include "Tile.h"



Tile::Tile(){}

Tile::Tile(int _tile_ID, ResourceHolder* _rh): tile_ID(_tile_ID), rh(_rh)
{
	tile_shape.setSize(sf::Vector2f(tile_size, tile_size));
	tile_shape.setTexture(&rh->tiles);
	int x = tile_size * (tile_ID % rh->tiles_width);
	int y = tile_size * (tile_ID / rh->tiles_width);
	tile_shape.setTextureRect(sf::IntRect(x, y, tile_size, tile_size));
}


Tile::~Tile()
{
}
