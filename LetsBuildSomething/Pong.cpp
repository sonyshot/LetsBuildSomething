#include "Pong.h"


Pong::Pong() {
	//player 2 on the left, because of the way I bound key inputs
	m_player2.setFillColor(sf::Color::White);
	m_player2.setPosition(sf::Vector2f(50, 450));
	m_player2.setSize(sf::Vector2f(20, 80));

	//player 1 on the right...
	m_player1.setFillColor(sf::Color::White);
	m_player1.setPosition(sf::Vector2f(900, 450));
	m_player1.setSize(sf::Vector2f(20, 80));

	m_dividingLine.setFillColor(sf::Color::White);
	m_dividingLine.setPosition(sf::Vector2f(497, 0));
	m_dividingLine.setSize(sf::Vector2f(6, 1000));

	m_ball.setFillColor(sf::Color::White);
	m_ball.setPosition(sf::Vector2f(500, 500));
	m_ball.setRadius(10);
	m_ballXv = 3;
	m_ballYv = 5;
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
	target.draw(m_ball);
	target.draw(m_dividingLine);
}

bool Pong::checkCollision() {
	if (m_ball.getGlobalBounds().intersects(m_player1.getGlobalBounds())) {
		m_ballXv = -1 * m_ballXv;
		return true;
	} else 
	return false;
}

void Pong::movePlayers() {
	//if (m_moving1[0]) {
	//	//player 1 left
	//	m_player1.move(sf::Vector2f(-5, 0));
	//}
	if (m_moving1[1]) {
		//player 1 up
		m_player1.move(sf::Vector2f(0, -m_paddleSpeed));
	}
	//if (m_moving1[2]) {
	//	//player 1 right
	//	m_player1.move(sf::Vector2f(5, 0));
	//}
	if (m_moving1[3]) {
		//player 1 down
		m_player1.move(sf::Vector2f(0, m_paddleSpeed));
	}
	//if (m_moving2[0]) {
	//	//player 2 left
	//	m_player2.move(sf::Vector2f(-5, 0));
	//}
	if (m_moving2[1]) {
		//player 2 up
		m_player2.move(sf::Vector2f(0, -m_paddleSpeed));
	}
	//if (m_moving2[2]) {
	//	//player 2 right
	//	m_player2.move(sf::Vector2f(5, 0));
	//}
	if (m_moving2[3]) {
		//player 2 down
		m_player2.move(sf::Vector2f(0, m_paddleSpeed));
	}
}

void Pong::moveBall() {
	m_ball.move(m_ballXv, m_ballYv);
	//if ((m_ball.getGlobalBounds().left < 0) || (m_ball.getGlobalBounds().left > m_screenX - 20)) {
	//	m_ballXv = -1 * m_ballXv;
	//	std::cout << "Point" << std::endl;
	//}
	if ((m_ball.getGlobalBounds().top < 0) || (m_ball.getGlobalBounds().top > m_screenY - 20)) {
		m_ballYv = -1 * m_ballYv;
	}
}

void Pong::update() {
	movePlayers();
	checkCollision();
	moveBall();
}