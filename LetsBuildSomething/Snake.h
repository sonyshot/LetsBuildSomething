#pragma once

#include "Game.h"

class Snake : public Game {

	std::vector<sf::RectangleShape*> m_snake;
	std::vector<sf::RectangleShape*> m_verticalLines;
	std::vector<sf::RectangleShape*> m_horizontalLines;
	sf::RectangleShape m_background;
	sf::RectangleShape *m_apple;

	int m_count = 0;
	int m_score = 0;
	int m_snakeSize = 1;
	bool m_gameOver = false;
	bool m_appleExists = false;
	bool moving = false;
	int m_width;
	int m_height;
	////////////////////////////up, right, down, left
	std::array<bool, 4> m_moving = { 0, 0, 0, 0 };
	bool checkOutOfBounds();
	bool checkCollision();
	bool checkApple();
	void addNewSquare();
	void removeLastSquare();
	void stopMoving();
	void gameOver();
	void makeApple();
	void increaseSize();

public:
	Snake(int sizeX, int sizeY, StateManager * manager);

	~Snake();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);

	void update();





};