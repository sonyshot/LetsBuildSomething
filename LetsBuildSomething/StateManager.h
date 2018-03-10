#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Pong.h"
#include "Snake.h"
#include "MainMenu.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//WHEN ADDING GAME: ADD STATE HERE, CONSTRUCTOR TO STATEMANAGER.CPP, ADD QUEUESWITCH TO MAINMENU's CHOOSEGAME()
//MAKE YOUR SURE CONSTRUCTOR TAKES IN AND ASSIGNS THE STATEMANAGER POINTER TO m_stateManager
enum PossibleStates { MENUSTATE, PONGSTATE, SNAKESTATE};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class StateManager {
	//contains the logic for switching between games, handling all that kinda stuff
	//enum or enum class better?

	Game * m_currentGame;

	PossibleStates m_currentState;
	PossibleStates m_nextState;

	sf::RenderWindow * m_window;

	void switchState(PossibleStates);

public:
	StateManager();

	StateManager(sf::RenderWindow *window);

	~StateManager();

	void queueSwitch(PossibleStates);

	void processEvent(sf::Event &e);

	void update();

	void draw();
};



#endif