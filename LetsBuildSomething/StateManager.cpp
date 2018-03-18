#include "StateManager.h"

StateManager::StateManager() {

}

StateManager::StateManager(sf::RenderWindow *window) {
	m_window = window;
	m_currentGame = new MainMenu(this);
	m_currentState = MENUSTATE;
	std::cout << "Game created" << std::endl;
}

StateManager::~StateManager() {
	delete m_currentGame;
	std::cout << "Game destroyed" << std::endl;
}

void StateManager::switchState(PossibleStates newState) {
	//need to properly implement this; currently just testing how it works
	//ADD CONSTRUCTOR FOR YOUR GAME HERE INSIDE ITS OWN ELSE IF
	delete m_currentGame;
	if (newState == MENUSTATE) {
		m_currentGame = new MainMenu(this);
		m_currentState = newState;
	}
	else if (newState == PONGSTATE) {
		m_currentGame = new Pong(sf::Vector2f(0,0), sf::Vector2f(800, 600), this);
		m_currentState = newState;
	}
	else if (newState == SNAKESTATE) {
		m_currentGame = new Snake(800, 800, this);
		m_currentState = newState;
	}
	else if (newState == TETRISSTATE) {
		m_currentGame = new Tetris(sf::Vector2f(0, 0), sf::Vector2f(800, 800), sf::Vector2f(10, 30),this);
		m_currentState = TETRISSTATE;
	}
}

void StateManager::queueSwitch(PossibleStates state) {
	m_nextState = state;
}

void StateManager::processEvent(sf::Event &e) {
	m_currentGame->handleEvent(e);
	//eventually should add a way for the manager to interface with the games
	//maybe escape will be a universal pause button that allows switches?
}

void StateManager::update() {
	//call current game update
	m_currentGame->update();
	if (m_nextState != m_currentState) {
		switchState(m_nextState);
	}

}

void StateManager::draw() {
	//call current game draw method
	m_window->clear();

	m_window->draw(*m_currentGame);

	m_window->display();
}