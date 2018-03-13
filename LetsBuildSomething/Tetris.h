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

	int m_interval = 30;
	int m_frames = 0;

	void createNextPiece(PieceType);

	void movePiece(int x, int y);
	void rotatePiece();
	bool checkCollision(int moveX, int moveY, bool);
	void clearRow(int);

	int m_blockSize = 20;
	int m_pieceStartxPos = 400;
	int m_pieceStartyPos = 400;

	bool m_paused = 0;

	TetrisPiece m_piece;

	void pieceToBlocks();

public:
	Tetris(StateManager*);

	~Tetris();

	void update();

	void handleEvent(const sf::Event &e);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif