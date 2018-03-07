#pragma once
#ifndef PONG_H
#define PONG_H

#include "Game.h"

class Pong : public Game {

	sf::RectangleShape m_player1;
	sf::RectangleShape m_player2;

	std::array<bool, 4> m_moving1 = { 0, 0, 0 ,0 };
	std::array<bool, 4> m_moving2 = { 0, 0, 0, 0 };

	void movePlayers();

public:
	Pong();

	~Pong();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);

	void reset();

	void update();
};



#endif
