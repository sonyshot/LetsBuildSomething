#include "Tetris.h"
#include "StateManager.h"

Tetris::Tetris(StateManager* sm) :m_filledGrid(), m_backdrop(sf::Vector2f(200, 600)), m_piece(PIECE2, m_blockSize) {
	//assuming 10x30 grid for now
	m_backdrop.setPosition(300, 0);
	m_backdrop.setFillColor(sf::Color::Green);
	m_piece.setPosition(400, 0);
	m_blocks.setPrimitiveType(sf::Quads);
	m_stateManager = sm;
}

Tetris::~Tetris() {
	
}

void Tetris::createNextPiece(PieceType type) {
	//lets work on making a copy constructor later
	m_piece = TetrisPiece(type, m_blockSize);
	m_piece.setPosition(400, 0);
}

void Tetris::movePiece(int x, int y) {
	//left, right, and down are standard
	m_piece.move(m_blockSize*x, m_blockSize*y);
}

void Tetris::rotatePiece() {

}

bool Tetris::checkCollision(int moveX, int moveY) {
	//check if any of the blocks of the piece have something beneath them
	//more generally, check if blocks have something in the direction theyre moving
	for (int i = 0; i < 4; i++) {
		//15 hardcoded as offset from left of screen
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2*i] - 15;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2*i + 1];
		//grid is 10x30, thats where these hardcoded numbers come from
		if (blockY + moveY == 30)
			return true;
		if ((blockX + moveX < 0) || (blockX + moveX > 9))
			return true;
		if (m_filledGrid[blockX + moveX + 10*(blockY+moveY)])
			return true;
	}
	return false;
}

void Tetris::clearRow(int row) {

}

void Tetris::pieceToBlocks() {
	//convert a piece into a collection of blocks that can be individually deleted when rows clear
	for (int i = 0; i < 16; i++) {
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2*(i / 4)] - 15;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2*(i / 4) + 1];
		if (i % 4 == 0) {
			m_filledGrid[blockX + 10 * blockY] = 1;
		}
		m_blocks.append(sf::Vertex(m_piece[i].position + m_piece.getPosition()));
	}
}

void Tetris::update() {
	//need a better way to wait 30 frames before doing stuff
	if (!m_paused) {
		if (++m_frames / 30 >= 1) {
			m_frames = 0;
			if (checkCollision(0, 1)) {
				pieceToBlocks();
				createNextPiece(PIECE4);
			}
			movePiece(0, 1);
		}
	}
	//move piece according to input (handled elsewhere currently)
	//every *interval* move down one unit
	//-if that move down puts it inside another block, freeze it and generate a new piece
}

void Tetris::handleEvent(const sf::Event &e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Down) {
			if (!checkCollision(0, 1)) {
				movePiece(0, 1);
			}
		}
		else if (e.key.code == sf::Keyboard::Left) {
			if (!checkCollision(-1, 0)) {
				movePiece(-1, 0);
			}
		}
		else if (e.key.code == sf::Keyboard::Right) {
			if (!checkCollision(1, 0)) {
				movePiece(1, 0);
			}
		}
		else if (e.key.code == sf::Keyboard::Up) {
			rotatePiece();
		}
		else if (e.key.code == sf::Keyboard::Escape) {
			queueSwitch(MENUSTATE);
		}
		else if (e.key.code == sf::Keyboard::Space) {
			std::cout << "piece x: " << m_piece.getPosition().x / m_blockSize << "\npiece y: " << m_piece.getPosition().y / m_blockSize << std::endl;
			m_paused = !m_paused;
		}
	}
}

void Tetris::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_backdrop);
	target.draw(m_piece);
	target.draw(m_blocks);
}