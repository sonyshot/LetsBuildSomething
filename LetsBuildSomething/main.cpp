#include "GameStateManager.h"

//test changes
int main() {

	float fps = 60.f;
	sf::Time sleepTime(sf::seconds(1.f / fps));
	sf::Clock clock;	

	sf::RenderWindow window(sf::VideoMode(800, 800), "board drawing test");

	GameStateManager gsm(&window);

	while (window.isOpen()) {
	
		//testing menu screen, etc.
		//game loop
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event)) {
		
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			gsm.keyPressed(event);
		}
		//maybe eventually wrap all the window loop into a gameState update function?
		//might make animations more doable
		gsm.update();
		gsm.draw();
		if (clock.getElapsedTime() < sleepTime) {
			sf::sleep(sleepTime - clock.getElapsedTime());
		}

	}


	return 0;
}

/*

Once finished with Pong, move on to creating the overview classes, statemanager and game

Games to implement:
-Pong
-Space Invaders
-Snake
-Asteroids
-Pac Man
-...

*/