#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
class ResourceHolder
{
public:
	ResourceHolder();
	~ResourceHolder();
	int s_width = 1600;
	int s_height = 1280;
	//Tilemap
	sf::Texture tiles;
	int tiles_width = 8;
	int tiles_height = 8;
	//FPS
	//Viewsq
	sf::View* view;
	sf::View* menu_view;
	sf::View* stat_view;
	sf::View* back_view;
	int status_bar_height = 100;
	double seconds_pr_frame = 0.016666667;
	//Image from paint to generate platform
	int no_of_maps = 3;
	std::vector<sf::Image> maps;
	int map_x;
	int map_y;
	sf::Image map_back;
	int tile_size = 64;
	//Background
	sf::Texture back_tex;
	sf::Sprite back_sprite;
	//Headline (intro message)
	sf::Text headline;
	//Player sprites
	sf::Texture player_gun;
	sf::Texture player_sword;
	sf::Texture jump_gun;
	sf::Texture jump_sword;
	std::vector<sf::Texture> sword_run;
	std::vector<sf::Texture> gun_run;
	std::vector<sf::Texture> shooting;
	std::vector<sf::Texture> player_die;
	//Enemy sprites
	std::vector<sf::Texture> enemy1_idle;
	sf::Texture enemy1_hit;

	std::vector<sf::Texture> enemy2;
	//Crystal sprites
	std::vector<sf::Texture> crystals;
	//Diamond
	std::vector<sf::Texture> diamond;
	//Fonts
	sf::Font font1;
	//Sounds
	sf::SoundBuffer b_game_over;
	sf::Sound s_game_over;
	sf::SoundBuffer b_death;
	sf::Sound s_death;
	sf::SoundBuffer b_fall;
	sf::Sound s_fall;
	sf::SoundBuffer b_cheer;
	sf::Sound s_cheer;
	sf::SoundBuffer b_shot;
	sf::Sound s_shot;
	sf::SoundBuffer b_monster_death;
	sf::Sound s_monster_death;
	sf::SoundBuffer b_gem;
	sf::Sound s_gem;
	sf::SoundBuffer b_jump;
	sf::Sound s_jump;
	sf::Music music1;

};

