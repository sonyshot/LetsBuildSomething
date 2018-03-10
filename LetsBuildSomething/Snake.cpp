#include "Snake.h"
#include "StateManager.h"

Snake::Snake(int x, int y, StateManager * manager) {
	width = x;
	height = y;
	m_stateManager = manager;
	background.setFillColor(sf::Color(50, 50, 50));
	background.setPosition(sf::Vector2f(0, 0));
	background.setSize(sf::Vector2f(800, 800));
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
	m_snake[m_snakeSize - 1]->setFillColor(sf::Color::Yellow);
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
}


void Snake::handleEvent(const sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W) {
			stopMoving();
			m_moving[0] = 1;
		}
		if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::D) {
			stopMoving();
			m_moving[1] = 1;
		}
		if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S) {
			stopMoving();
			m_moving[2] = 1;
		}
		if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::A) {
			stopMoving();
			m_moving[3] = 1;
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
	target.draw(background);
	for (sf::RectangleShape* cell : m_snake) {
		target.draw(*cell);
	}
	for (sf::RectangleShape* line : m_verticalLines) {
		target.draw(*line);
	}
	for (sf::RectangleShape* line : m_horizontalLines) {
		target.draw(*line);
	}

	
}
void Snake::update() {
	move();
	checkOutOfBounds();
	checkCollision();

}

void Snake::move() {
	if (m_moving[0]) {
		m_snake[0]->move(0, -40);
	} 
	if (m_moving[1]) {
		m_snake[0]->move(40, 0);
	}
	if (m_moving[2]) {
		m_snake[0]->move(0, 40);
	}
	if (m_moving[3]) {
		m_snake[0]->move(-40, 0);
	}
}

bool Snake::checkCollision() {
	return false;
}

bool Snake::checkOutOfBounds() {
	return false;
}