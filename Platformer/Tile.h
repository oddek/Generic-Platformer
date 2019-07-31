#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
class Tile
{
public:
	Tile();
	Tile(int _tile_ID, ResourceHolder* _rh);
	~Tile();
	
	int tile_ID;

	sf::RectangleShape tile_shape;

	int tile_size = 64;

	ResourceHolder* rh;
};

