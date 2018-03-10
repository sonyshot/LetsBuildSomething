#include "MainMenu.h"
#include "StateManager.h"

MainMenu::MainMenu(StateManager * sm) {
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->setFillColor(sf::Color(50, 100, 200));
		//exploiting layout of 3x2 grid for constructor, should be generalized?
		m_buttons[i]->setPosition(sf::Vector2f(50 + 250*(i%3), 300 + 250*(i/3)));
		m_buttons[i]->setSize(sf::Vector2f(200, 200));
		m_buttons[i]->setOutlineColor(sf::Color::White);
	}

	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		std::cout << "failed to load font" << std::endl;
	
	m_selectName.setFont(m_font);
	m_selectName.setFillColor(sf::Color::White);
	m_selectName.setPosition(sf::Vector2f(50, 300));
	m_selectName.setString("Pong");

	m_headerText.setFont(m_font);
	m_headerText.setFillColor(sf::Color::White);
	m_headerText.setString("GAMES");
	m_headerText.setCharacterSize(64);
	m_headerText.setPosition(sf::Vector2f(400 - m_headerText.getLocalBounds().width / 2, 100));


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
			m_selectName.setPosition(m_buttons[m_currentSelection]->getPosition());
		}
		else if (e.key.code == sf::Keyboard::Right) {
			//add to current selection
			m_buttons[m_currentSelection]->setOutlineThickness(0.f);
			m_currentSelection = (m_currentSelection + 1) % m_numButtons;
			m_buttons[m_currentSelection]->setOutlineThickness(5.f);
			m_selectName.setPosition(m_buttons[m_currentSelection]->getPosition());
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

}

void MainMenu::update() {

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (sf::RectangleShape* button : m_buttons)
		target.draw(*button);
	target.draw(m_selectName);
	target.draw(m_headerText);
}