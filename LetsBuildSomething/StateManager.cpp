#include "StateManager.h"

StateManager::StateManager() {

}

StateManager::StateManager(sf::RenderWindow *window) {
	m_window = window;
	m_currentGame = new MainMenu;
	m_gametype = MENUSTATE;
	std::cout << "Game created" << std::endl;
}

StateManager::~StateManager() {
	delete m_currentGame;
	std::cout << "Game destroyed" << std::endl;
}

void StateManager::switchState() {
	//need to properly implement this; currently just testing how it works
	delete m_currentGame;
	if (m_gametype == MENUSTATE) {
		m_currentGame = new Pong(800, 600);
		m_gametype = PONGSTATE;
	}
	else if (m_gametype == PONGSTATE) {
		m_currentGame = new MainMenu();
		m_gametype = MENUSTATE;
	}
}

void StateManager::processEvent(sf::Event &e) {
	m_currentGame->handleEvent(e);
	//eventually should add a way for the manager to interface with the games
	//maybe escape will be a universal pause button that allows switches?
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
		switchState();
}

void StateManager::update() {
	//call current game update
	m_currentGame->update();

}

void StateManager::draw() {
	//call current game draw method
	m_window->clear();

	m_window->draw(*m_currentGame);

	m_window->display();
}