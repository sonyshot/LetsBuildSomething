#include "Snake.h"

Snake::Snake(GameStateManager *m_gsm) {
	gsm = m_gsm;
	
}

Snake::~Snake() {
	
}


void Snake::keyPressed(const sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Escape) {
			gsm->setState(0);
		}
	}
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Text text;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	text.setString("Snake State");
	text.setFillColor(sf::Color::White);
	text.setFont(font);
	text.setPosition(50, 50);
	target.draw(text);
	text.setString("Escape to go back");
	text.setPosition(50, 100);
	target.draw(text);
}

void Snake::update() {

}