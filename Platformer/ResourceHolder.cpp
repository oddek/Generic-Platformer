#include "ResourceHolder.h"



ResourceHolder::ResourceHolder()
{

	//Load map and tiles
	tiles.loadFromFile("img/Tiles_64x64.png");
	for (int i = 0; i < no_of_maps; i++)
	{
		sf::Image map;
		map.loadFromFile("img/levels/" + std::to_string(i) + ".png");
		maps.push_back(map);
	}
	map_x = maps[1].getSize().x;
	map_y = maps[1].getSize().y;
	//Load back_map and background
	back_tex.loadFromFile("img/sky.png");
	back_sprite.setTexture(back_tex);
	back_sprite.setScale(2, 1);
	map_back.loadFromFile("img/map1_back.png");
	//Setup views
	view = new sf::View(sf::FloatRect(0, 0, s_width, s_height));
	menu_view = new sf::View(sf::FloatRect(0, 0, s_width, s_height));
	stat_view = new sf::View(sf::FloatRect(0, 0, s_width, status_bar_height));
	stat_view->setViewport(sf::FloatRect(0, 0, 1, 0.1));
	view->setCenter((maps[0].getSize().x*tile_size) / 2, s_height / 2);
	//Load player sprites
	player_sword.loadFromFile("img/Hero-Guy-PNG/_Mode-Sword/01-Idle/JK_P_Sword__Idle_000.png");
	player_gun.loadFromFile("img/Hero-Guy-PNG/_Mode-Gun/01-Idle/JK_P_Gun__Idle_000.png");
	jump_gun.loadFromFile("img/Hero-Guy-PNG/_Mode-Gun/05-Jump/JK_P_Gun__Jump_000.png");
	jump_sword.loadFromFile("img/Hero-Guy-PNG/_Mode-Sword/05-Jump/JK_P_Sword__Jump_000.png");
	for (int i = 0; i <= 9; i++)
	{
		sf::Texture rg;
		sf::Texture rs;
		
		sf::Texture die;
		sf::Texture shoot;

		rg.loadFromFile("img/Hero-Guy-PNG/_Mode-Gun/02-Run/JK_P_Gun__Run_00" + std::to_string(i) + ".png");
		rs.loadFromFile("img/Hero-Guy-PNG/_Mode-Sword/02-Run/JK_P_Sword__Run_00" + std::to_string(i) + ".png");
		die.loadFromFile("img/Hero-Guy-PNG/06-Die/JK_P__Die_00" + std::to_string(i) + ".png");
		shoot.loadFromFile("img/Hero-Guy-PNG/_Mode-Gun/03-Shot/JK_P_Gun__Attack_00" + std::to_string(i) + ".png");

		sword_run.push_back(rs);
		gun_run.push_back(rg);
		player_die.push_back(die);
		shooting.push_back(shoot);
	}

	//Load enemy sprites
	//Enemy 1 idle:
	for (int i = 1; i <= 2; i++)
	{
		sf::Texture en1_id;
		en1_id.loadFromFile("img/monster1/idle/frame-" + std::to_string(i) + ".png");
		enemy1_idle.push_back(en1_id);
	}
	enemy1_hit.loadFromFile("img/monster1/got_hit/frame.png");
	//Enemy 2 idle:
	for (int i = 1; i <= 4; i++)
	{
		sf::Texture en2_id;
		en2_id.loadFromFile("img/monster2/" + std::to_string(i) + ".png");
		enemy2.push_back(en2_id);
	}
	//Load crystals
	for (int i = 0; i < 6; i++)
	{
		sf::Texture t;
		t.loadFromFile("img/crystals/" + std::to_string(i) + ".png");
		crystals.push_back(t);
	}

	//Load Diamond
	for (int i = 1; i < 61; i++)
	{
		sf::Texture t;
		if (i < 10)
			t.loadFromFile("img/diamond/000" + std::to_string(i) + ".png");
		else
			t.loadFromFile("img/diamond/00" + std::to_string(i) + ".png");

		diamond.push_back(t);
	}

	//Load fonts
	font1.loadFromFile("fonts/neuropol_x_rg.ttf");
	//Setup headline
	headline.setCharacterSize(120);
	headline.setFont(font1);
	headline.setFillColor(sf::Color(0x009a00FF));
	headline.setOutlineColor(sf::Color(0x000000FF));
	headline.setOutlineThickness(10);
	headline.setStyle(sf::Text::Bold);
	headline.setString("Start!");
	auto text_rect = headline.getGlobalBounds();
	headline.setOrigin(text_rect.width / 2, text_rect.height / 2);
	headline.setPosition(view->getCenter());
	//Load sounds
	b_game_over.loadFromFile("sound/game_over.wav");
	s_game_over.setBuffer(b_game_over);

	b_death.loadFromFile("sound/death.wav");
	s_death.setBuffer(b_death);

	b_fall.loadFromFile("sound/fall.wav");
	s_fall.setBuffer(b_fall);

	b_cheer.loadFromFile("sound/cheer.wav");
	s_cheer.setBuffer(b_cheer);

	b_shot.loadFromFile("sound/shot.wav");
	s_shot.setBuffer(b_shot);
	s_shot.setVolume(60);
	
	b_monster_death.loadFromFile("sound/monster_death.wav");
	s_monster_death.setBuffer(b_monster_death);

	b_gem.loadFromFile("sound/gem.wav");
	s_gem.setBuffer(b_gem);

	b_jump.loadFromFile("sound/jump.wav");
	s_jump.setBuffer(b_jump);

	music1.openFromFile("sound/home.ogg");
	music1.setVolume(40);

}


ResourceHolder::~ResourceHolder()
{
}
