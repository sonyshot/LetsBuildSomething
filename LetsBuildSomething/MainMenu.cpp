#include "MainMenu.h"

MainMenu::MainMenu() {
	m_button1.setFillColor(sf::Color(255, 100, 100));
	m_button1.setPosition(sf::Vector2f(100, 100));
	m_button1.setSize(sf::Vector2f(50, 50));

	m_button2.setFillColor(sf::Color(200, 200, 200));
	m_button2.setPosition(sf::Vector2f(200, 100));
	m_button2.setSize(sf::Vector2f(50, 50));
}

MainMenu::~MainMenu() {

}

void MainMenu::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		//change selection; select game
		break;
	}
}

void MainMenu::update() {

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_button1);
	target.draw(m_button2);
}