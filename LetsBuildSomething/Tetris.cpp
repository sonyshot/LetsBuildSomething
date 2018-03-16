#include "Tetris.h"
#include "StateManager.h"

Tetris::Tetris(StateManager* sm) :m_filledGrid(), m_backdrop(sf::Vector2f(200, 600)),m_gameOverLay(sf::Vector2f(200, 600)), m_piece(randomPiece(), m_blockSize) {
	//assuming 10x30 grid for now
	m_backdrop.setPosition(300, 0);
	m_backdrop.setFillColor(sf::Color::Green);
	m_gameOverLay.setPosition(300, 0);
	m_gameOverLay.setFillColor(sf::Color(75, 75, 75, 100));
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

PieceType Tetris::randomPiece() {
	int choice = rand() % 7;
	switch (choice) {
	case 0:
		return PIECE1;
	case 1:
		return PIECE2;
	case 2:
		return PIECE3;
	case 3:
		return PIECE4;
	case 4:
		return PIECE5;
	case 5:
		return PIECE6;
	case 6:
		return PIECE7;
	}

}

void Tetris::movePiece(int x, int y) {
	//left, right, and down are standard
	m_piece.move(m_blockSize*x, m_blockSize*y);
}

void Tetris::rotatePiece() {
	m_piece.rotatePiece();
}

bool Tetris::checkCollision(int moveX, int moveY, bool isRotation = 0) {
	//check if any of the blocks of the piece have something beneath them
	//more generally, check if blocks have something in the direction theyre moving
	for (int i = 0; i < 4; i++) {
		//15 hardcoded as offset from left of screen
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2*i] - 15;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2*i + 1];
		//grid is 10x30, thats where these hardcoded numbers come from
		if (isRotation && (blockX + moveX + m_piece.rotateGrowth() > 9))
			return true;
		if (blockY + moveY == 30)
			return true;
		if ((blockX + moveX < 0) || (blockX + moveX > 9))
			return true;
		if (m_filledGrid[blockX + moveX + 10*(blockY+moveY)])
			return true;
	}
	return false;
}

int Tetris::rowsToClear() {
	//hardcoded 30 rows~ and 10 columns~~~~~~~~~~~~~~
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 10; j++) {
			if (!m_filledGrid[j + i * 10])
				break;
			if (j == 9)
				return i;
		}
	}
	return -1;
}

void Tetris::isGameOver() {
	if(checkCollision(0, 1)){
		//gameover screen eventually
		m_gameOver = 1;
	}
}

void Tetris::clearRow(int row) {
	//looking like the way to go is to dupe m_blocks, clear m_blocks, loop and only include vertices not in that row, shift them down
	//if not the way mentioned above, then maybe need to have separate objects store rows and just wipe those as theyre filled
	sf::VertexArray storBlocks = m_blocks;
	m_blocks.clear();
	for (int i = 29; i > 0; i--) {
		if (i > row)
			continue;
		for (int j = 0; j < 10; j++) {
			m_filledGrid[j + i * 10] = m_filledGrid[j + (i-1) * 10];
			if (i == 1)
				m_filledGrid[j] = 0;
		}
	}

	for (int i = 0; i < storBlocks.getVertexCount()/4; i++) {
		//hardcoding for 10x30 grid with size 20 blocks
		int quadRow = storBlocks[4 * i].position.y / 20;
		if (quadRow == row)
			continue;
		for (int j = 0; j < 4; j++) {
			if (quadRow > row) {
				sf::Vertex nVert(storBlocks[j + 4 * i]);
				nVert.color = storBlocks[j + 4 * i].color;
				m_blocks.append(nVert);
			}
			else {
				sf::Vector2f offset(0, m_blockSize);
				sf::Vertex nVert(sf::Vector2f(storBlocks[j + 4 * i].position) + offset);
				nVert.color = storBlocks[j + 4 * i].color;
				m_blocks.append(nVert);
			}

		}
	}
}

void Tetris::pieceToBlocks() {
	//convert a piece into a collection of blocks that can be individually deleted when rows clear
	for (int i = 0; i < 16; i++) {
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2*(i / 4)] - 15;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2*(i / 4) + 1];
		if (i % 4 == 0) {
			m_filledGrid[blockX + 10 * blockY] = 1;
		}
		sf::Vertex nVert(m_piece[i].position + m_piece.getPosition());
		nVert.color = m_piece.m_color;
		m_blocks.append(nVert);
	}
}

void Tetris::update() {
	//need a better way to wait 30 frames before doing stuff
	//update gettin a litttle long, maybe divide up the work
	if (m_gameOver)
		return;
	if (!m_paused) {
		if (++m_frames / 30 >= 1) {
			m_frames = 0;
			//forced movement, move into own function?
			if (checkCollision(0, 1)) {
				pieceToBlocks();
				int test = rowsToClear();
				while (test != -1) {
					clearRow(test);
					test = rowsToClear();
				}
				createNextPiece(randomPiece());
				isGameOver();
			}
			else {
				movePiece(0, 1);
			}
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
			if (!checkCollision(0, 0, 1))
				rotatePiece();
		}
		else if (e.key.code == sf::Keyboard::Escape) {
			queueSwitch(MENUSTATE);
		}
		else if (e.key.code == sf::Keyboard::Space) {
			//restart if game over
			m_paused = !m_paused;
		}
	}
}

void Tetris::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_backdrop);
	target.draw(m_piece);
	target.draw(m_blocks);
	if (m_gameOver)
		target.draw(m_gameOverLay);
}