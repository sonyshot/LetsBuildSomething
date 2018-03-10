#include "Snake.h"

Snake::Snake(int x, int y) {
	width = x;
	height = y;
	for (int i = 0; i < 20; i++) {
		m_verticalLines.push_back(new sf::RectangleShape);
		m_verticalLines[i]->setFillColor(sf::Color::White);
		m_verticalLines[i]->setSize(sf::Vector2f(1, 1000));
		m_verticalLines[i]->setPosition(sf::Vector2f(40 * i, 0));
	}
	for (int i = 0; i < 20; i++) {
		m_horizontalLines.push_back(new sf::RectangleShape);
		m_horizontalLines[i]->setFillColor(sf::Color::White);
		m_horizontalLines[i]->setSize(sf::Vector2f(1000, 1));
		m_horizontalLines[i]->setPosition(sf::Vector2f(0, 40 * i));
	}
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
			m_moving[0] = 1;
		}
	}
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

}