#include "TetrisPiece.h"

TetrisPiece::TetrisPiece(PieceType type, int size) :m_vertices(sf::Quads, 16), m_blockSize(size), m_blockPositions() {
	createPiece(type);
}

TetrisPiece::~TetrisPiece() {

}

void TetrisPiece::rotatePiece() {
	for (int j = 0; j < 4; j++) {
		int newX = m_rows - m_blockPositions[2 * j + 1] - 1;

		int yj = m_blockPositions[2 * j + 1] = m_blockPositions[2 * j];
		int xj = m_blockPositions[2 * j] = newX;
		for (int i = 0; i < 4; i++) {
			//using these allows us to set the quad corners clockwise
			int xiIter = ((i + 1) / 2) % 2;
			int yiIter = i / 2;
			m_vertices[i + 4 * j].position = sf::Vector2f(m_blockSize * (xj + xiIter), m_blockSize * (yj + yiIter));
		}
	}
	int tempRow = m_cols;
	m_cols = m_rows;
	m_rows = tempRow;
}

int TetrisPiece::rotateGrowth() {
	return m_rows - m_cols;
}

sf::Vertex TetrisPiece::operator[](int index) {
	return m_vertices[index];
}

std::array<int, 8> TetrisPiece::getBlockPositions() {
	return m_blockPositions;
}

void TetrisPiece::createPiece(PieceType type) {
	if (type == PIECE1) {
		m_rows = 4;
		m_cols = 1;
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
		m_rows = 3;
		m_cols = 2;
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
		m_rows = 4;
		m_cols = 1;
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
		m_rows = 3;
		m_cols = 2;
		std::array<int, 4> xjIters{ 0, 0, 1, 0 };
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
		m_rows = 2;
		m_cols = 2;
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
		m_rows = 3;
		m_cols = 2;
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
		m_rows = 3;
		m_cols = 2;
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