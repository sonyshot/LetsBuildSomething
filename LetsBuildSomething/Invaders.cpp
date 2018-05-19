#include "Invaders.h"
#include "StateManager.h"

Invaders::Invaders(sf::Vector2f position, sf::Vector2f size, StateManager * sm) {

}

Invaders::~Invaders() {

}

void Invaders::movePlayer(int speed) {
	m_player.move(sf::Vector2f(speed, 0));
}

void Invaders::update() {

}

void Invaders::handleEvent(const sf::Event &e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Down) {
			//player can't move down
		}
		else if (e.key.code == sf::Keyboard::Left) {
			//move left
		}
		else if (e.key.code == sf::Keyboard::Right) {
			//move right
		}
		else if (e.key.code == sf::Keyboard::Up) {
			//player can't move up
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

void Invaders::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}
