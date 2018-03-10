#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Game.h"

class MainMenu : public Game {

	sf::RectangleShape m_button1, m_button2, m_button3, m_button4, m_button5;
	//leave empty, fill with buttons? maybe better to just hardcode since it'll be constant anyway the start
	std::vector<sf::RectangleShape*> m_buttons = { &m_button1, &m_button2, &m_button3, &m_button4, &m_button5 };

	int m_numButtons = 5;

	int m_currentSelection = 0;

	void chooseGame(int);

public:
	//inherits queueswitch
	MainMenu(StateManager *);

	~MainMenu();

	void handleEvent(const sf::Event &e);

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif