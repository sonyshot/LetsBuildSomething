#pragma once
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameStateManager.h"


class MenuState : public GameState {
	GameStateManager *gsm;
	int m_currentSelection = 0;
	std::string options[4] = { "Menu", "Pong", "Snake", "Quit" };
	sf::Text text;
	void select(int m_currentSelection);
public:
	MenuState(GameStateManager *m_gsm);

	~MenuState();

	void keyPressed(const sf::Event &e);

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif