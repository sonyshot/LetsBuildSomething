#include "Tetris.h"
#include "StateManager.h"

Tetris::Tetris(sf::Vector2f position, sf::Vector2f size, sf::Vector2f grid, StateManager* sm) 
	:m_blockSize(20), m_filledGrid(grid.x*grid.y,0), m_backdrop(sf::Vector2f(m_blockSize*grid.x, m_blockSize*grid.y)),m_gameOverLay(sf::Vector2f(m_blockSize*grid.x, m_blockSize*grid.y)), m_piece(randomPiece(), m_blockSize),m_nextPiece(randomPiece(),m_blockSize), m_grid(grid) {
	//blocksize still hardcoded at 20
	m_screenX = position.x;
	m_screenW = size.x;
	m_screenY = position.y;
	m_screenH = size.y;

	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		std::cout << "Failed to load font" << std::endl;

	m_scoreText.setFont(m_font);
	m_scoreText.setPosition(position);
	m_scoreText.setString(std::to_string(m_score));
	
	m_backdrop.setPosition(m_screenX + (m_screenW - m_blockSize*m_grid.x)/2, m_screenY);
	m_backdrop.setFillColor(sf::Color::Green);
	m_gameOverLay.setPosition(m_screenX + (m_screenW - m_blockSize * m_grid.x) / 2, m_screenY);
	m_gameOverLay.setFillColor(sf::Color(75, 75, 75, 100));
	m_piece.setPosition(m_screenX+m_screenW/2, m_screenY);
	//hardcoded offset
	m_nextPiece.setPosition(m_screenX + m_screenW - 50, m_screenY);
	m_blocks.setPrimitiveType(sf::Quads);
	m_stateManager = sm;
}

Tetris::~Tetris() {
	
}

void Tetris::createNextPiece(PieceType type) {
	//lets work on making a copy constructor later
	m_piece = m_nextPiece;
	m_nextPiece = TetrisPiece(type, m_blockSize);
	m_nextPiece.setPosition(m_screenX + m_screenW - 50, m_screenY);
	m_piece.setPosition(m_screenX + m_screenW / 2, m_screenY);
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

void Tetris::queueMove(int movePos) {
	//0 is left, 1 is rotate, 2 is right, 3 is down
	m_moveQueue = { 0, 0, 0, 0 };
	m_moveQueue[movePos] = 1;
}

void Tetris::movePiece() {
	//left, right, and down are standard
	if (m_moveQueue[1] && !checkCollision(0, 0, 1)) {
		rotatePiece();
		m_moveQueue = { 0,0,0,0 };
	}
	else if (m_moveQueue[0] && !checkCollision(-1, 0)) {
		m_piece.move(sf::Vector2f(-m_blockSize, 0));
		m_moveQueue = { 0,0,0,0 };
	}
	else if (m_moveQueue[2] && !checkCollision(1, 0)) {
		m_piece.move(sf::Vector2f(m_blockSize, 0));
		m_moveQueue = { 0,0,0,0 };
	}
	else if (m_moveQueue[3] && !checkCollision(0, 1)) {
		m_piece.move(sf::Vector2f(0, m_blockSize));
		m_moveQueue = { 0,0,0,0 };
	}
}

void Tetris::rotatePiece() {
	m_piece.rotatePiece();
}

bool Tetris::checkCollision(int moveX, int moveY, bool isRotation) {
	//check if any of the blocks of the piece have something beneath them
	//more generally, check if blocks have something in the direction theyre moving
	for (int i = 0; i < 4; i++) {
		//15 hardcoded as offset from left of screen
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2 * i] - (m_screenX + (m_screenW - m_blockSize * m_grid.x) / 2) / m_blockSize;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2 * i + 1] - m_screenY / m_blockSize;
		//grid is 10x30, thats where these hardcoded numbers come from
		if (isRotation && (blockX + moveX + m_piece.rotateGrowth() > 9))
			return true;
		if (blockY + moveY == m_grid.y)
			return true;
		if ((blockX + moveX < 0) || (blockX + moveX > m_grid.x-1))
			return true;
		if (m_filledGrid[blockX + moveX + m_grid.x*(blockY+moveY)])
			return true;
	}
	return false;
}

int Tetris::rowsToClear() {
	//hardcoded 30 rows~ and 10 columns~~~~~~~~~~~~~~
	for (int i = 0; i < m_grid.y; i++) {
		for (int j = 0; j < m_grid.x; j++) {
			if (!m_filledGrid[j + i * m_grid.x])
				break;
			if (j == m_grid.x-1)
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
	for (int i = m_grid.y - 1; i > 0; i--) {
		if (i > row)
			continue;
		for (int j = 0; j < m_grid.x; j++) {
			m_filledGrid[j + i * m_grid.x] = m_filledGrid[j + (i-1) * m_grid.x];
			if (i == 1)
				m_filledGrid[j] = 0;
		}
	}

	for (int i = 0; i < storBlocks.getVertexCount()/4; i++) {
		//hardcoding for 10x30 grid with size 20 blocks
		int quadRow = storBlocks[4 * i].position.y / m_blockSize;
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
		int blockX = m_piece.getPosition().x / m_blockSize + m_piece.getBlockPositions()[2*(i / 4)] - (m_screenX + (m_screenW - m_blockSize * m_grid.x) / 2) / m_blockSize;
		int blockY = m_piece.getPosition().y / m_blockSize + m_piece.getBlockPositions()[2*(i / 4) + 1] - m_screenY / m_blockSize;
		if (i % 4 == 0) {
			m_filledGrid[blockX + 10 * blockY] = 1;
		}
		sf::Vertex nVert(m_piece[i].position + m_piece.getPosition());
		nVert.color = m_piece.m_color;
		m_blocks.append(nVert);
	}
}

void Tetris::addPoints(int rowsCleared) {
	m_score += 50;
	if (rowsCleared < 4)
		m_score += 125 * rowsCleared;
	else
		m_score += 250 * rowsCleared;
	m_scoreText.setString(std::to_string(m_score));
}

void Tetris::increaseDropSpeed() {
	//increase drop speed up to a max
	//hard coding when its increased and max
	//max is dropping 12 times a second
	if (m_interval == 5)
		return;
	//every 3 rows, increase speed; 30 hardcoded as starting interval
	m_interval--;
}

void Tetris::forcedMove() {
	//makes the piece move down to the bottom
	if (checkCollision(0, 1)) {
		pieceToBlocks();
		int row = rowsToClear();
		int numCleared = 0;
		while (row != -1) {
			clearRow(row);
			numCleared++;
			row = rowsToClear();
			increaseDropSpeed();
		}
		m_numRowsCleared += numCleared;
		addPoints(numCleared);
		createNextPiece(randomPiece());
		isGameOver();
	}
	else
		m_piece.move(0, m_blockSize);
}

void Tetris::update() {
	//need a better way to wait 30 frames before doing stuff
	//move piece according to input (handled elsewhere currently)
	//every *interval* move down one unit
	//-if that move down puts it inside another block, freeze it and generate a new piece
	if (m_gameOver)
		return;
	if (!m_paused) {
		movePiece();
		if (++m_frames%m_interval == 0) {
			//forced movement, move into own function?
			forcedMove();
		}
	}
}

void Tetris::handleEvent(const sf::Event &e) {
	//this needs to instead queue a move in the update function
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Down) {
			m_moveQueue = { 0,0,0,0 };
			m_moveQueue[3] = 1;
		}
		else if (e.key.code == sf::Keyboard::Left) {
			m_moveQueue = { 0,0,0,0 };
			m_moveQueue[0] = 1;
		}
		else if (e.key.code == sf::Keyboard::Right) {
			m_moveQueue = { 0,0,0,0 };
			m_moveQueue[2] = 1;
		}
		else if (e.key.code == sf::Keyboard::Up) {
			m_moveQueue = { 0,0,0,0 };
			m_moveQueue[1] = 1;
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
	target.draw(m_nextPiece);
	target.draw(m_blocks);
	target.draw(m_scoreText);
	if (m_gameOver)
		target.draw(m_gameOverLay);
}