#include "Game.h"
#include "StateManager.h"

void Game::queueSwitch(PossibleStates newState) {
	m_stateManager->queueSwitch(newState);
}