#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Game.h"
#include "TetrisPiece.h"

class Tetris :public Game {
	//1 is long, 2 is "L", 3 is mirror of "L", 4 is the fork one, 5 is square, 6 is steps, 7 is mirror of steps
	sf::Font m_font;
	sf::Text m_scoreText;

	int m_blockSize = 20;
	std::vector<bool> m_filledGrid;
	std::array<bool, 4> m_moveQueue = { 0, 0, 0, 0 };
	sf::VertexArray m_blocks;
	//instead of this, should there be separate arrays for each row?

	sf::RectangleShape m_backdrop;
	sf::RectangleShape m_gameOverLay;

	int m_numRowsCleared = 0;
	int m_interval = 12;
	int m_frames = 0;

	void createNextPiece(PieceType);
	PieceType randomPiece();

	void movePiece();
	void rotatePiece();
	bool checkCollision(int, int, bool rot =0);
	int rowsToClear();
	void clearRow(int);

	sf::Vector2f m_grid;
	int m_pieceStartxPos = 400;
	int m_pieceStartyPos = 400;
	int m_score = 0;

	bool m_paused = 0;
	bool m_gameOver = 0;

	TetrisPiece m_nextPiece;
	TetrisPiece m_piece;

	void queueMove(int);
	void increaseDropSpeed();
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