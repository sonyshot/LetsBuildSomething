#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Game.h"

class MainMenu : public Game {

	//might want to programmatically create these (ie feed number of buttons to the constructor)
	sf::RectangleShape m_button1, m_button2, m_button3, m_button4, m_button5, m_button6;
	std::vector<sf::RectangleShape*> m_buttons = { &m_button1, &m_button2, &m_button3, &m_button4, &m_button5, &m_button6 };

	//is it a good idea to have a bunch of mappings? it feels right...
	std::unordered_map<int, PossibleStates> m_selToStateMap;
	std::unordered_map<PossibleStates, std::string> m_stateToNameMap;

	sf::Font m_font;
	sf::Text m_headerText;
	sf::Text m_selectName;

	int m_numButtons = 6;

	int m_currentSelection = 0;

	void selectIcon(int);

public:
	//inherits queueswitch
	MainMenu(StateManager *);

	~MainMenu();

	void handleEvent(const sf::Event &e);

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif