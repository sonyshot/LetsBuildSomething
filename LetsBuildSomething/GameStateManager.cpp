#include "Pong.h"
#include "MenuState.h"
#include "Snake.h"


GameStateManager::GameStateManager() {

}


GameStateManager::GameStateManager(sf::RenderWindow *window) {
	m_window = window;
	setState(MENUSTATE);
	m_gameStates[0] = new MenuState(this);
	m_gameStates[1] = new Pong(this);
	m_gameStates[2] = new Snake(this);
//	m_gameStates[3] = new Quit(this);
//add new games here as needed
	std::cout << "Game created" << std::endl;

}


GameStateManager::~GameStateManager() {
	for (GameState *state : m_gameStates) {
		delete state;
	}
}

void GameStateManager::setState(int state) {
	m_currentState = state;
}

int GameStateManager::getState() {
	return m_currentState;
}

void GameStateManager::keyPressed(sf::Event &e) {
	m_gameStates[m_currentState]->keyPressed(e);
}

void GameStateManager::update() {
	
}

void GameStateManager::draw() {
	//call current game draw method
	m_window->clear();

	m_window->draw(*m_gameStates[m_currentState]);

	m_window->display();
}