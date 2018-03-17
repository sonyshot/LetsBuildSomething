#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H
//PHYSICS GAME PogChamp
#include "Game.h"

class Physics : public Game {


public:
	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);
};



#endif // !PHYSICS_H
