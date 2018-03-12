#include "TetrisPiece.h"

TetrisPiece::TetrisPiece(PieceType type, int size) :m_vertices(sf::Quads, 16), m_blockSize(size), m_blockPositions() {
	createPiece(type);
}

TetrisPiece::~TetrisPiece() {

}

sf::Vertex TetrisPiece::operator[](int index) {
	return m_vertices[index];
}

std::array<int, 8> TetrisPiece::getBlockPositions() {
	return m_blockPositions;
}

void TetrisPiece::rotatePiece() {

}

void TetrisPiece::createPiece(PieceType type) {
	if (type == PIECE1) {
		std::array<int, 4> xjIters{ 0, 0, 0, 0 };
		std::array<int, 4> yjIters{ 0, 1, 2, 3 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2*j] = xjIters[j];
			m_blockPositions[2*j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4*j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE2) {
		std::array<int, 4> xjIters{ 0, 0, 0, 1 };
		std::array<int, 4> yjIters{ 0, 1, 2, 2 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE3) {
		std::array<int, 4> xjIters{ 1, 1, 1, 0 };
		std::array<int, 4> yjIters{ 0, 1, 2, 2 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE4) {
		std::array<int, 4> xjIters{ 0, 0, 1, 0};
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE5) {
		std::array<int, 4> xjIters{ 0, 1, 0, 1 };
		std::array<int, 4> yjIters{ 0, 0, 1, 1 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE6) {
		std::array<int, 4> xjIters{ 1, 1, 0, 0 };
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE7) {
		std::array<int, 4> xjIters{ 0, 0, 1, 1 };
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_blockPositions[2 * j] = xjIters[j];
			m_blockPositions[2 * j + 1] = yjIters[j];
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = ((i + 1) / 2) % 2;
				int yiIter = i / 2;
				m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xjIters[j] + xiIter), m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
}


void TetrisPiece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//apply transforms
	states.transform *= getTransform();

	//apply texture

	target.draw(m_vertices, states);
}