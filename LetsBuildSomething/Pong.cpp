#include "Pong.h"


Pong::Pong() {
	m_player1.setFillColor(sf::Color::White);
	m_player1.setPosition(sf::Vector2f(50, 50));
	m_player1.setSize(sf::Vector2f(80, 40));

	m_player2.setFillColor(sf::Color::White);
	m_player2.setPosition(sf::Vector2f(50, 50));
	m_player2.setSize(sf::Vector2f(80, 40));
}

Pong::~Pong() {

}

void Pong::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Left) {
			m_moving1[0] = 1;
		}
		else if (e.key.code == sf::Keyboard::Up) {
			m_moving1[1] = 1;
		}
		else if (e.key.code == sf::Keyboard::Right) {
			m_moving1[2] = 1;
		}
		else if (e.key.code == sf::Keyboard::Down) {
			m_moving1[3] = 1;
		}
		else if (e.key.code == sf::Keyboard::A) {
			m_moving2[0] = 1;
		}
		else if (e.key.code == sf::Keyboard::W) {
			m_moving2[1] = 1;
		}
		else if (e.key.code == sf::Keyboard::D) {
			m_moving2[2] = 1;
		}
		else if (e.key.code == sf::Keyboard::S) {
			m_moving2[3] = 1;
		}
		break;

	case sf::Event::KeyReleased:
		if (e.key.code == sf::Keyboard::Left) {
			m_moving1[0] = 0;
		}
		else if (e.key.code == sf::Keyboard::Up) {
			m_moving1[1] = 0;
		}
		else if (e.key.code == sf::Keyboard::Right) {
			m_moving1[2] = 0;
		}
		else if (e.key.code == sf::Keyboard::Down) {
			m_moving1[3] = 0;
		}
		else if (e.key.code == sf::Keyboard::A) {
			m_moving2[0] = 0;
		}
		else if (e.key.code == sf::Keyboard::W) {
			m_moving2[1] = 0;
		}
		else if (e.key.code == sf::Keyboard::D) {
			m_moving2[2] = 0;
		}
		else if (e.key.code == sf::Keyboard::S) {
			m_moving2[3] = 0;
		}
		break;
	}
}

void Pong::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_player1);
	target.draw(m_player2);
}

void Pong::movePlayers() {
	if (m_moving1[0]) {
		//player 1 left
		m_player1.move(sf::Vector2f(-5, 0));
	}
	if (m_moving1[1]) {
		//player 1 up
		m_player1.move(sf::Vector2f(0, -5));
	}
	if (m_moving1[2]) {
		//player 1 right
		m_player1.move(sf::Vector2f(5, 0));
	}
	if (m_moving1[3]) {
		//player 1 down
		m_player1.move(sf::Vector2f(0, 5));
	}
	if (m_moving2[0]) {
		//player 2 left
		m_player2.move(sf::Vector2f(-5, 0));
	}
	if (m_moving2[1]) {
		//player 2 up
		m_player2.move(sf::Vector2f(0, -5));
	}
	if (m_moving2[2]) {
		//player 2 right
		m_player2.move(sf::Vector2f(5, 0));
	}
	if (m_moving2[3]) {
		//player 2 down
		m_player2.move(sf::Vector2f(0, 5));
	}
}

void Pong::update() {
	movePlayers();
}