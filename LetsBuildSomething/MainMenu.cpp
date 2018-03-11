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

	//ADD GAME'S TILE HERE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	m_selToStateMap[0] = PONGSTATE;
	m_selToStateMap[1] = SNAKESTATE;
	m_selToStateMap[2] = TETRISSTATE;
	//GAME'S TITLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	m_stateToNameMap[PONGSTATE] = "Pong";
	m_stateToNameMap[SNAKESTATE] = "Snake";
	m_stateToNameMap[TETRISSTATE] = "Tetris";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	m_buttons[m_currentSelection]->setOutlineThickness(5.f);

	m_stateManager = sm;
}

MainMenu::~MainMenu() {

}

void MainMenu::selectIcon(int offset) {
	//takes offset in to determine which to select
	m_buttons[m_currentSelection]->setOutlineThickness(0.f);
	m_currentSelection = (m_currentSelection + m_numButtons + offset) % m_numButtons;
	m_buttons[m_currentSelection]->setOutlineThickness(5.f);
	if (m_stateToNameMap.count(m_selToStateMap[m_currentSelection]))
		m_selectName.setString(m_stateToNameMap[m_selToStateMap[m_currentSelection]]);
	else
		m_selectName.setString("(unknown)");
	m_selectName.setPosition(m_buttons[m_currentSelection]->getPosition());
}

void MainMenu::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		//change selection; select game
		//feels bad copypasting these lines, maybe make separate function?
		if (e.key.code == sf::Keyboard::Left) {
			selectIcon(-1);
		}
		else if (e.key.code == sf::Keyboard::Right) {
			selectIcon(1);
		}
		else if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down) {
			//uses fact that each row has 3 icons with total of 6
			selectIcon(3);
		}
		else if (e.key.code == sf::Keyboard::Return) {
			queueSwitch(m_selToStateMap[m_currentSelection]);
		}
		break;

	case sf::Event::MouseMoved:
		for (int i = 0; i < m_buttons.size(); i++) {
			if (m_buttons[i]->getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y))) {
				selectIcon(i - m_currentSelection);
				break;
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (m_buttons[m_currentSelection]->getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)) {
			queueSwitch(m_selToStateMap[m_currentSelection]);
		}
		break;
	}
}

void MainMenu::update() {

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (sf::RectangleShape* button : m_buttons)
		target.draw(*button);
	target.draw(m_selectName);
	target.draw(m_headerText);
}