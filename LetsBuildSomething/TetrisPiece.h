#pragma once
#ifndef TETRISPIECE_H
#define TETRISPIECE_H

#include "SFML\Graphics.hpp"
#include <array>

enum PieceType { PIECE1, PIECE2, PIECE3, PIECE4, PIECE5, PIECE6, PIECE7 };

class TetrisPiece :public sf::Drawable, public sf::Transformable{

	sf::VertexArray m_vertices;

	int m_blockSize = 10;
	int m_rows = 0;
	int m_cols = 0;

	std::array<int, 8> m_blockPositions;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	TetrisPiece(PieceType, int);

	~TetrisPiece();

	sf::Vertex operator[](int index);

	std::array<int, 8> getBlockPositions();

	void rotatePiece();
	
	//i'm pretty sure this is a bad way to do this...
	int rotateGrowth();

	void createPiece(PieceType);
};


#endif // !TETRISPIECE_H
