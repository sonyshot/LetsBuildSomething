#include "Game.h"
#include "StateManager.h"

Game::~Game(){}

void Game::queueSwitch(PossibleStates newState) {
	m_stateManager->queueSwitch(newState);
}