#pragma once
#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "GameState.h"

class GameStateManager {
	//contains the logic for switching between games, handling all that kinda stuff
	//enum or enum class better?

	GameState* m_gameStates[4];
	int m_currentState;

	sf::RenderWindow * m_window;


public:
	int MENUSTATE = 0;
	int PONGSTATE = 1;
	int SNAKESTATE = 2;
	int QUIT = 3;

	GameStateManager();
	
	GameStateManager(sf::RenderWindow *window);

	~GameStateManager();

	void setState(int state);

	int getState();

	void keyPressed(sf::Event &e);

	void update();

	void draw();
};



#endif