#include <SFML\Graphics.hpp>
#include "StateManager.h"
#include <fstream>

//test changes
int main()
{
	srand(0);
	float fps = 60.f;
	sf::Time sleepTime(sf::seconds(1.f / fps));
	sf::Clock clock;	

	sf::RenderWindow window(sf::VideoMode(800, 800), "board drawing test", sf::Style::None);

	StateManager snm(&window);

	while (window.isOpen())
	{
		//testing menu screen, etc.
		//game loop
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			};
			snm.processEvent(event);
		}
		//maybe eventually wrap all the window loop into a gameState update function?
		//might make animations more doable
		snm.update();
		snm.draw();
		if (clock.getElapsedTime() < sleepTime)
			sf::sleep(sleepTime - clock.getElapsedTime());

	};


	return 0;
};

/*

Games to implement:
-Pong *sufficient*
-Space Invaders
-Snake *sufficient*
-Asteroids
-Pac Man
-tetris *sufficient*
-cards?
-...

Other to do:
-score tracking/stats
--create serialization technique

*/