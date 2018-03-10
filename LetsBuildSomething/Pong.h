#pragma once
#ifndef PONG_H
#define PONG_H

#include "GameStateManager.h"

class Pong : public GameState {
	GameStateManager *gsm;

	sf::RectangleShape m_player1;
	sf::RectangleShape m_player2;
	sf::CircleShape m_ball;
	sf::RectangleShape m_dividingLine;
	sf::RectangleShape m_screen;

	sf::Font m_font;
	std::array<sf::Text, 2> m_scores;
	int m_score1 = 0;
	int m_score2 = 0;

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
	Pong(GameStateManager *m_gsm);

	Pong(int x, int y);

	~Pong();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void keyPressed(const sf::Event &e);

	void update();
};



#endif

/*
TODO:
-currently good enough for government work
-comment!
-Scoreboard (DONE)
-more generality in the constructor (ie should the pong object be centered, settable starting velocities, etc.)
-pause/exit menu
-revisit update function
-randomly chosen start velocities
*/
