#include <SFML/Graphics.hpp>
#include "Screen_1.h"
#include "ResourceHolder.h"



//#TODO:
/*
Legg til idle animasjon
credits skjerm?

Friksjon

Stomp attack

Flere fiender, flygende?

Trykk 'b' for å løpe fortere?

Flere baner

BUGS:
Klipper inn i blokker iblant: mulig løsning, flytt x og oppdater current tile før du sjekker y
****TROR DETTE ER LØST NÅ!********

*/

int main()
{
	srand(time(0));
	ResourceHolder rh;
	rh.music1.play();
	rh.music1.setLoop(true);
	sf::RenderWindow window(sf::VideoMode(rh.s_width, rh.s_height), "Platformer");
	window.setKeyRepeatEnabled(false);
	std::vector<cScreen*> Screens;
	int screen = 0;

	cScreen* s0 = new Screen_1(&rh);
	Screens.push_back(s0);
	while (screen <= 0)
	{
		screen = Screens[screen]->Run(window);
		if (screen == 0) break;
		if (screen == 2)
		{
			delete Screens[0];
			cScreen* s0 = new Screen_1(&rh);
			Screens.push_back(s0);
			screen = 0;
		}
	}
	return 0;
}


