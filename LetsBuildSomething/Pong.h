#pragma once
#ifndef PONG_H
#define PONG_H

#include "Game.h"

class Pong : public Game {

	sf::RectangleShape m_player1;
	sf::RectangleShape m_player2;
	sf::CircleShape m_ball;
	sf::RectangleShape m_dividingLine;
	sf::RectangleShape m_screen;

	int m_screenX = 1000;
	int m_screenY = 1000;

	int m_playStart = 0;
	std::array<bool, 4> m_moving1 = { 0, 0, 0 ,0 };
	std::array<bool, 4> m_moving2 = { 0, 0, 0, 0 };
	int m_ballXv = 0;
	int m_ballYv = 0;
	int m_paddleSpeed = 10;
	int m_ballRadius = 10;

	bool checkCollision();
	void moveBall();
	void movePlayers();

	void newRound();

public:
	Pong();

	Pong(int sizeX, int sizeY);

	~Pong();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);

	void update();
};



#endif

/*
TODO:
-comment!
-Scoreboard
-more generality in the constructor (ie should the pong object be centered, settable starting velocities, etc.)
-pause/exit menu
-revisit update function
-randomly chosen start velocities
*/
