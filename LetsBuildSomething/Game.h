#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <array>

class Game : public sf::Drawable {
	//base class for all games to be added to this hot mess
	//any game that will exist just basically needs to be able to be drawn and handle events/inputs


public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual void handleEvent(const sf::Event &e) = 0;
};



#endif
