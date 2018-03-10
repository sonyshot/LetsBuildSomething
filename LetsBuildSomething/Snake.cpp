#include "Snake.h"
#include "StateManager.h"

Snake::Snake(int x, int y, StateManager * manager) {
	m_width = x;
	m_height = y;
	m_stateManager = manager;
	m_background.setFillColor(sf::Color(50, 50, 50));
	m_background.setPosition(sf::Vector2f(0, 0));
	m_background.setSize(sf::Vector2f(800, 800));
	for (int i = 0; i < 20; i++) {
		m_verticalLines.push_back(new sf::RectangleShape);
		m_verticalLines[i]->setFillColor(sf::Color(150, 150, 150));
		m_verticalLines[i]->setSize(sf::Vector2f(1, 800));
		m_verticalLines[i]->setPosition(sf::Vector2f(40 * i, 0));
	}
	for (int i = 0; i < 20; i++) {
		m_horizontalLines.push_back(new sf::RectangleShape);
		m_horizontalLines[i]->setFillColor(sf::Color(150, 150, 150));
		m_horizontalLines[i]->setSize(sf::Vector2f(800, 1));
		m_horizontalLines[i]->setPosition(sf::Vector2f(0, 40 * i));
	}
	m_snake.push_back(new sf::RectangleShape);
	m_snake[m_snakeSize - 1]->setFillColor(sf::Color(200, 200, 0));
	m_snake[m_snakeSize - 1]->setSize(sf::Vector2f(40, 40));
	m_snake[m_snakeSize - 1]->setPosition(sf::Vector2f(400, 400));

}

Snake::~Snake() {
	for (sf::RectangleShape* line : m_verticalLines) {
		delete line;
	}
	for (sf::RectangleShape* line : m_horizontalLines) {
		delete line;
	}
	for (sf::RectangleShape* cell : m_snake) {
		delete cell;
	}
}


void Snake::handleEvent(const sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		moving = true;
		if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W) {
			if (!m_moving[2]) {
				stopMoving();
				m_moving[0] = 1;
			}
		}
		if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::D) {
			if (!m_moving[3]) {
				stopMoving();
				m_moving[1] = 1;
			}
		}
		if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S) {
			if (!m_moving[0]) {
				stopMoving();
				m_moving[2] = 1;
			}
		}
		if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::A) {
			if (!m_moving[1]) {
				stopMoving();
				m_moving[3] = 1;
			}
		}
		if (e.key.code == sf::Keyboard::Escape) {
			queueSwitch(MENUSTATE);
		}
	}
}

void Snake::stopMoving() {
	m_moving[0] = 0;
	m_moving[1] = 0;
	m_moving[2] = 0;
	m_moving[3] = 0;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background);
	for (sf::RectangleShape* cell : m_snake) {
		target.draw(*cell);
	}
	for (sf::RectangleShape* line : m_verticalLines) {
		target.draw(*line);
	}
	for (sf::RectangleShape* line : m_horizontalLines) {
		target.draw(*line);
	}
	if (m_gameOver) {
		sf::Font font;
		sf::Text text;
		font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
		text.setString("Game Over! Escape to exit");
		text.setFont(font);
		text.setPosition(200, 400);
		target.draw(text);
	}
	if (m_appleExists) {
		target.draw(*m_apple);
	}
	
}
void Snake::update() {
	if (!m_gameOver) {
		if (!m_appleExists) {
			makeApple();
		}
		if (m_count > 5 && moving) {
			addNewSquare();
			removeLastSquare();
			m_count = 0;
		}
		if (checkOutOfBounds() || checkCollision()) {
			gameOver();
		}
		if (checkApple()) {
			increaseSize();
			delete m_apple;
			m_appleExists = false;
		}
		m_count++;
	}
}

void Snake::addNewSquare() {
	sf::RectangleShape *newSquare = new sf::RectangleShape();
	newSquare->setFillColor(sf::Color(200, 200, 0));
	newSquare->setSize(sf::Vector2f(40, 40));
	int x = m_snake[m_snakeSize - 1]->getGlobalBounds().left;
	int y = m_snake[m_snakeSize - 1]->getGlobalBounds().top;
	if (m_moving[0] == 1) {
		newSquare->setPosition(sf::Vector2f(x, y - 40));
	} 
	if (m_moving[1] == 1) {
		newSquare->setPosition(sf::Vector2f(x + 40, y));
	}
	if (m_moving[2] == 1) {
		newSquare->setPosition(sf::Vector2f(x, y + 40));
	}
	if (m_moving[3] == 1) {
		newSquare->setPosition(sf::Vector2f(x - 40, y));
	}
	m_snake.push_back(newSquare);
}

void Snake::removeLastSquare() {
	if (m_snake.size() > m_snakeSize) {
		m_snake.erase(m_snake.begin());
	}
}

bool Snake::checkCollision() {
	if (m_snakeSize > 2) {
		for (int i = m_snakeSize - 2; i > 0; i--) {
			int headX = m_snake[m_snakeSize - 1]->getGlobalBounds().left;
			int headY = m_snake[m_snakeSize - 1]->getGlobalBounds().top;
			if (headX == m_snake[i]->getGlobalBounds().left && headY == m_snake[i]->getGlobalBounds().top) {
				return true;
			}
		}
		return false;
	}
	return false;
}

bool Snake::checkOutOfBounds() {
	if (m_snake[m_snakeSize - 1]->getGlobalBounds().top < 0) {
		return true;
	}
	if (m_snake[m_snakeSize - 1]->getGlobalBounds().top + 40 > 800) {
		return true;
	}
	if (m_snake[m_snakeSize - 1]->getGlobalBounds().left < 0) {
		return true;
	}
	if (m_snake[m_snakeSize - 1]->getGlobalBounds().left + 40 > 800) {
		return true;
	}
	return false;
}

bool Snake::checkApple() {
	if ((m_snake[m_snakeSize - 1]->getGlobalBounds().left == m_apple->getGlobalBounds().left) && (m_snake[m_snakeSize - 1]->getGlobalBounds().top == m_apple->getGlobalBounds().top)) {
		return true;
	}
	return false;
}

void Snake::gameOver() {
	m_gameOver = true;
	m_appleExists = false;
	delete m_apple;
}

void Snake::makeApple() {
	m_apple = new sf::RectangleShape();
	m_apple->setFillColor(sf::Color::Red);
	int x = std::rand() % 20 + 1;
	int y = std::rand() % 20 + 1;
	m_apple->setPosition(x * 40, y * 40);
	m_apple->setSize(sf::Vector2f(40, 40));
	m_appleExists = true;
}

void Snake::increaseSize() {
	addNewSquare();
	m_snakeSize++;
}