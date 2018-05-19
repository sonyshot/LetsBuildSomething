#pragma once
#ifndef INVADERS_H
#define INVADERS_H

#include "Game.h"

class Invaders :public Game {

	bool m_paused = 0;

	sf::RectangleShape m_player;

	void movePlayer(int moveAmount);

public:
	Invaders(sf::Vector2f position, sf::Vector2f size, StateManager *);

	~Invaders();

	void update();

	void handleEvent(const sf::Event &e);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // !INVADERS_H

