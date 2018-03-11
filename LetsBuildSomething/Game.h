#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <math.h>

class StateManager;

enum PossibleStates;

class Game : public sf::Drawable {
	//base class for all games to be added to this hot mess
	//any game that will exist just basically needs to be able to update, be drawn, and handle events
protected:

	StateManager * m_stateManager;

	void queueSwitch(PossibleStates);

public:
	virtual ~Game() = 0;

	virtual void update() = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void handleEvent(const sf::Event &e) = 0;
};


#endif
