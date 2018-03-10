#pragma once
#ifndef SNAKE_H
#define SNAKE_H
#include <vector>

#include "GameStateManager.h"


class Snake : public GameState {
	GameStateManager *gsm;

	std::vector<sf::RectangleShape> m_lines;

public:
	Snake(GameStateManager *m_gsm);

	~Snake();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void keyPressed(const sf::Event &e);

	void update();

};


#endif