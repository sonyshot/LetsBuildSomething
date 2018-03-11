#pragma once
#ifndef TETRIS_H
#define TETRIS_H

#include "Game.h"

class Tetris :public Game {
	//1 is long, 2 is "L", 3 is mirror of "L", 4 is the fork one, 5 is square, 6 is steps, 7 is mirror of steps
	enum PieceType{PIECE1, PIECE2, PIECE3, PIECE4, PIECE5, PIECE6, PIECE7};

	std::array<bool, 300> m_filledGrid{};
	std::vector<sf::VertexArray*> m_blocks;

	std::array<sf::VertexArray*, 4> m_nextPiece;

	void createNextPiece(PieceType);

	int m_blockSize = 10;
	int m_pieceStartxPos = 400;
	int m_pieceStartyPos = 400;


public:
	Tetris(StateManager*);

	~Tetris();

	void update();

	void handleEvent(const sf::Event &e);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif