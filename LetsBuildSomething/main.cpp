#include <SFML\Graphics.hpp>
#include "Pong.h"

//test changes
int main()
{
	float fps = 60.f;
	sf::Time sleepTime(sf::seconds(1.f / fps));
	sf::Clock clock;

	Pong pong;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "board drawing test");

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
			pong.handleEvent(event);
		}
		//maybe eventually wrap all the window loop into a gameState update function?
		//might make animations more doable
		pong.update();
		window.clear();
		window.draw(pong);
		window.display();
		if (clock.getElapsedTime() < sleepTime)
			sf::sleep(sleepTime - clock.getElapsedTime());

	};


	return 0;
};