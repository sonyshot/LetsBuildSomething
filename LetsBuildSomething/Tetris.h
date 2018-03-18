#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Game.h"
#include "TetrisPiece.h"

class Tetris :public Game {
	//1 is long, 2 is "L", 3 is mirror of "L", 4 is the fork one, 5 is square, 6 is steps, 7 is mirror of steps

	std::array<bool, 300> m_filledGrid;
	sf::VertexArray m_blocks;
	//instead of this, should there be separate arrays for each row?

	sf::RectangleShape m_backdrop;
	sf::RectangleShape m_gameOverLay;

	int m_interval = 30;
	int m_frames = 0;

	void createNextPiece(PieceType);
	PieceType randomPiece();

	void movePiece(int x, int y);
	void rotatePiece();
	bool checkCollision(int moveX, int moveY, bool);
	//this needs to be array eventually
	int rowsToClear();
	void clearRow(int);

	sf::Vector2f m_grid;
	int m_blockSize = 30;
	int m_pieceStartxPos = 400;
	int m_pieceStartyPos = 400;
	int m_score = 0;

	bool m_paused = 0;
	bool m_gameOver = 0;

	TetrisPiece m_piece;

	void addPoints(int numCleared);
	void forcedMove();
	void pieceToBlocks();
	void isGameOver();

public:
	Tetris(sf::Vector2f position, sf::Vector2f size, sf::Vector2f grid, StateManager*);

	~Tetris();

	void update();

	void handleEvent(const sf::Event &e);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif

/*
Still need to implement increasing drop speed, fix rotations, check RNG as it seems weird, scoring
*/