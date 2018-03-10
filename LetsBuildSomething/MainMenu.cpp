#include "MainMenu.h"

MainMenu::MainMenu() {
	m_button1.setFillColor(sf::Color(255, 100, 100));
	m_button1.setPosition(sf::Vector2f(100, 100));
	m_button1.setSize(sf::Vector2f(50, 50));
	m_button1.setOutlineColor(sf::Color::White);

	m_button2.setFillColor(sf::Color(200, 200, 200));
	m_button2.setPosition(sf::Vector2f(200, 100));
	m_button2.setSize(sf::Vector2f(50, 50));
	m_button2.setOutlineColor(sf::Color::White);

	m_button3.setFillColor(sf::Color(100, 255, 100));
	m_button3.setPosition(sf::Vector2f(300, 100));
	m_button3.setSize(sf::Vector2f(50, 50));
	m_button3.setOutlineColor(sf::Color::White);

	m_buttons[m_currentSelection]->setOutlineThickness(5.f);
}

MainMenu::~MainMenu() {

}

void MainMenu::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		//change selection; select game
		//should i add up/down support?
		if (e.key.code == sf::Keyboard::Left) {
			//subtract from current selection
			//replace mod with num choices variable
			m_buttons[m_currentSelection]->setOutlineThickness(0.f);
			m_currentSelection = (m_currentSelection + m_numButtons - 1) % m_numButtons;
			m_buttons[m_currentSelection]->setOutlineThickness(5.f);
		}
		else if (e.key.code == sf::Keyboard::Right) {
			//add to current selection
			m_buttons[m_currentSelection]->setOutlineThickness(0.f);
			m_currentSelection = (m_currentSelection + 1) % m_numButtons;
			m_buttons[m_currentSelection]->setOutlineThickness(5.f);
		}
		break;
	}
}

void MainMenu::update() {

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_button1);
	target.draw(m_button2);
	target.draw(m_button3);
}