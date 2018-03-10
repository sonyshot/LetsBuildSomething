#pragma once

#include "Game.h"

class Snake : public Game {

	std::vector<sf::RectangleShape*> m_snake;
	std::vector<sf::RectangleShape*> m_verticalLines;
	std::vector<sf::RectangleShape*> m_horizontalLines;
	sf::RectangleShape background;

	int m_score = 0;
	int m_snakeSize = 1;
	int width;
	int height;
	////////////////////////////up, right, down, left
	std::array<bool, 4> m_moving = { 0, 0, 0, 0 };
	bool checkOutOfBounds();
	bool checkCollision();
	void move();
	void stopMoving();

public:
	Snake(int sizeX, int sizeY, StateManager * manager);

	~Snake();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);

	void update();





};