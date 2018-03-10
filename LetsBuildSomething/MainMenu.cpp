#include "MainMenu.h"
#include "StateManager.h"

MainMenu::MainMenu(StateManager * sm) {
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->setFillColor(sf::Color(50*(i+1), 50 * (i + 1), 50 * (i + 1)));
		m_buttons[i]->setPosition(sf::Vector2f(100*(i+1), 100));
		m_buttons[i]->setSize(sf::Vector2f(50, 50));
		m_buttons[i]->setOutlineColor(sf::Color::White);
	}

	m_buttons[m_currentSelection]->setOutlineThickness(5.f);

	m_stateManager = sm;
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
		else if (e.key.code == sf::Keyboard::Return) {
			chooseGame(m_currentSelection);
		}
		break;
	}
}

void MainMenu::chooseGame(int choice) {
	//ADD QUEUESWITCH CALL TO YOUR ENUM
	if (choice == 0)
		queueSwitch(PONGSTATE);
	else if (choice == 1)
		queueSwitch(SNAKESTATE);
	else return;
}

void MainMenu::update() {

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (sf::RectangleShape* button : m_buttons)
		target.draw(*button);
}