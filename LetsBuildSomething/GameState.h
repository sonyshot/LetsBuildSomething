#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>
#include <stdio.h>

class GameState : public sf::Drawable {
	//base class for all games to be added to this hot mess
	//any game that will exist just basically needs to be able to update, be drawn, and handle events

public:
	virtual void update() = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void keyPressed(const sf::Event &e) = 0;
};



#endif
