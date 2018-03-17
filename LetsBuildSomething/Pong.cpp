#include "Pong.h"
#include "StateManager.h"

//need to work on good generic constructor
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

Pong::Pong(sf::Vector2f position, sf::Vector2f size, StateManager * sm) {
	
	//transform inputs to screen width and height
	m_screenX = position.x;
	m_screenW = size.x;
	m_screenY = position.y;
	m_screenH = size.y;
	m_stateManager = sm;

	m_screen.setFillColor(sf::Color::Transparent);
	m_screen.setOutlineColor(sf::Color::White);
	m_screen.setOutlineThickness(1);
	m_screen.setSize(sf::Vector2f(m_screenW, m_screenH));

	m_player2.setFillColor(sf::Color::White);
	m_player2.setPosition(sf::Vector2f(m_screenX +.05*m_screenW, m_screenY + .45*m_screenH));
	m_player2.setSize(sf::Vector2f(.02*m_screenW,.1*m_screenH));

	//player 1 on the right...
	m_player1.setFillColor(sf::Color::White);
	m_player1.setPosition(sf::Vector2f(m_screenX + .93*m_screenW, m_screenY + .45*m_screenH));
	m_player1.setSize(sf::Vector2f(.02*m_screenW, .1*m_screenH));

	m_dividingLine.setFillColor(sf::Color::White);
	m_dividingLine.setPosition(sf::Vector2f(m_screenX + .5*m_screenW - 1, m_screenY));
	m_dividingLine.setSize(sf::Vector2f(2, m_screenH));

	m_ballRadius = .01*m_screenW;
	m_ball.setFillColor(sf::Color::White);
	m_ball.setPosition(sf::Vector2f(m_screenX + .5*m_screenW - m_ballRadius, m_screenY + .5*m_screenH - m_ballRadius));
	m_ball.setRadius(m_ballRadius);
	//random starting velocity?
	m_ballXv = 3;
	m_ballYv = 5;

	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		std::cout << "failed to load font" << std::endl;
	

	m_scores[0].setFont(m_font);
	m_scores[0].setString(std::to_string(m_score1));
	m_scores[0].setFillColor(sf::Color::White);
	m_scores[0].setPosition(sf::Vector2f(.75*m_screenX, 700));
	m_scores[1].setFont(m_font);
	m_scores[1].setString(std::to_string(m_score2));
	m_scores[1].setFillColor(sf::Color::White);
	m_scores[1].setPosition(sf::Vector2f(.25*m_screenY, 700));
}

Pong::~Pong() {
	
}

void Pong::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		if (!m_playStart)
			m_playStart = 1;
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
		else if (e.key.code == sf::Keyboard::Escape) {
			//baby come back
			queueSwitch(MENUSTATE);
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
	target.draw(m_screen);
	target.draw(m_scores[0]);
	target.draw(m_scores[1]);
}

bool Pong::checkCollision() {
	if (m_ball.getGlobalBounds().intersects(m_player1.getGlobalBounds())) {
		m_ballXv = -1 * m_ballXv;
		return true;
	}
	else if (m_ball.getGlobalBounds().intersects(m_player2.getGlobalBounds())) {
		m_ballXv = -1 * m_ballXv;
		return true;
	}
	if (m_ball.getGlobalBounds().left < m_screenX) {
		std::cout << "Player 2 point!" << std::endl;
		m_score1 += 1;
		m_scores[0].setString(std::to_string(m_score1));
		newRound();
		return true;
	}
	else if (m_ball.getGlobalBounds().left > m_screenX + m_screenW) {
		std::cout << "Player 1 point!" << std::endl;
		m_score2 += 1;
		m_scores[1].setString(std::to_string(m_score2));
		newRound();
		return true;
	}

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
		if (m_player1.getGlobalBounds().top < m_screenY) {
			m_player1.setPosition(sf::Vector2f(m_screenX + .93*m_screenW, m_screenY));
			m_moving1[1] = 0;
		}
	}
	//if (m_moving1[2]) {
	//	//player 1 right
	//	m_player1.move(sf::Vector2f(5, 0));
	//}
	if (m_moving1[3]) {
		//player 1 down
		m_player1.move(sf::Vector2f(0, m_paddleSpeed));
		if (m_player1.getGlobalBounds().top > m_screenY + .9*m_screenH) {
			m_player1.setPosition(sf::Vector2f(m_screenX + .93*m_screenW, m_screenY + .9*m_screenH));
			m_moving1[3] = 0;
		}
	}
	//if (m_moving2[0]) {
	//	//player 2 left
	//	m_player2.move(sf::Vector2f(-5, 0));
	//}
	if (m_moving2[1]) {
		//player 2 up
		m_player2.move(sf::Vector2f(0, -m_paddleSpeed));
		if (m_player2.getGlobalBounds().top < m_screenY) {
			m_player2.setPosition(sf::Vector2f(m_screenX + .05*m_screenW, m_screenY));
			m_moving2[1] = 0;
		}
	}
	//if (m_moving2[2]) {
	//	//player 2 right
	//	m_player2.move(sf::Vector2f(5, 0));
	//}
	if (m_moving2[3]) {
		//player 2 down
		m_player2.move(sf::Vector2f(0, m_paddleSpeed));
		if (m_player2.getGlobalBounds().top > m_screenY + .9*m_screenH) {
			m_player2.setPosition(sf::Vector2f(m_screenX + .05*m_screenW, m_screenY + .9*m_screenH));
			m_moving2[3] = 0;
		}
	}
}

void Pong::moveBall() {
	m_ball.move(m_ballXv, m_ballYv);
	//if ((m_ball.getGlobalBounds().left < 0) || (m_ball.getGlobalBounds().left > m_screenX - 20)) {
	//	m_ballXv = -1 * m_ballXv;
	//	std::cout << "Point" << std::endl;
	//}
	if ((m_ball.getGlobalBounds().top < m_screenY) || (m_ball.getGlobalBounds().top > m_screenY + m_screenH - 2*m_ballRadius)) {
		m_ballYv = -1 * m_ballYv;
	}
}

void Pong::update() {
	//probably bad
	if (!m_playStart)
		return;
	movePlayers();
	moveBall();
	checkCollision();
}

void Pong::newRound() {
	m_playStart = 0;
	m_player2.setPosition(sf::Vector2f(m_screenX + .05*m_screenW, m_screenY + .45*m_screenH));
	m_player1.setPosition(sf::Vector2f(m_screenX + .93*m_screenW, m_screenY + .45*m_screenH));
	m_ball.setPosition(sf::Vector2f(m_screenX + .5*m_screenW - m_ballRadius, m_screenY + .5*m_screenH - m_ballRadius));
}