#include "Tetris.h"

Tetris::Tetris(StateManager* sm) {
	//assuming 10x30 grid for now

	createNextPiece(PIECE7);

	m_stateManager = sm;
}

Tetris::~Tetris() {
	for (sf::VertexArray* quad : m_nextPiece) {
		delete quad;
	}
}

void Tetris::createNextPiece(PieceType type) {
	if (type == PIECE1) {
		std::array<int, 4> xjIters{ 0, 0, 0, 0 };
		std::array<int, 4> yjIters{ 0, 1, 2, 3 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize*(xjIters[j]+ xiIter), m_pieceStartyPos + m_blockSize*(yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE2) {
		std::array<int, 4> xjIters{ 0, 0, 0, 1 };
		std::array<int, 4> yjIters{ 0, 1, 2, 2 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE3) {
		std::array<int, 4> xjIters{ 1, 1, 1, 0 };
		std::array<int, 4> yjIters{ 0, 1, 2, 2 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE4) {
		std::array<int, 4> xjIters{ 0, 0, 1, 0 };
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE5) {
		std::array<int, 4> xjIters{ 0, 1, 0, 1 };
		std::array<int, 4> yjIters{ 0, 0, 1, 1 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE6) {
		std::array<int, 4> xjIters{ 1, 1, 0, 0 };
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
	else if (type == PIECE7) {
		std::array<int, 4> xjIters{ 0, 0, 1, 1 };
		std::array<int, 4> yjIters{ 0, 1, 1, 2 };
		for (int j = 0; j < 4; j++) {
			m_nextPiece[j] = new sf::VertexArray(sf::Quads, 4);
			for (int i = 0; i < 4; i++) {
				//using these allows us to set the quad corners clockwise
				int xiIter = (i / 2) % 2;
				int yiIter = ((i + 1) / 2) % 2;
				m_nextPiece[j]->operator[](i).position = sf::Vector2f(m_pieceStartxPos + m_blockSize * (xjIters[j] + xiIter), m_pieceStartyPos + m_blockSize * (yjIters[j] + yiIter));
			}
		}
	}
}

void Tetris::update() {

}

void Tetris::handleEvent(const sf::Event &e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Down) {
			//do something
		}
	}
}

void Tetris::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (sf::VertexArray* quad : m_nextPiece) {
		target.draw(*quad);
	}
}