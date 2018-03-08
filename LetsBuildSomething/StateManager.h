#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Pong.h"
#include "MainMenu.h"

class StateManager {
	//contains the logic for switching between games, handling all that kinda stuff
	//enum or enum class better?

	//ADD YOUR GAME TO THIS ENUM, THAT WAY I CAN MAKE IT SELECTABLE IN THE MENU
	enum PossibleStates{MENUSTATE, PONGSTATE};
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	Game * m_currentGame;

	PossibleStates m_gametype;

	sf::RenderWindow * m_window;

	void switchState();

public:
	StateManager();

	StateManager(sf::RenderWindow *window);

	~StateManager();

	void processEvent(sf::Event &e);

	void update();

	void draw();
};



#endif