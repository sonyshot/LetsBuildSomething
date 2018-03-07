#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager {
	//contains the logic for switching between games, handling all that kinda stuff
	enum class PossibleStates{GAME1, GAME2, GAME3};
	
	PossibleStates m_currentGame;

public:
};



#endif