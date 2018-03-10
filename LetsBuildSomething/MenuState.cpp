#include "MenuState.h"

MenuState::MenuState(GameStateManager *m_gsm) {
	gsm = m_gsm;
	m_currentSelection = 1;
}

MenuState::~MenuState() {

}

void MenuState::keyPressed(const sf::Event &e) {
	if (e.type == sf::Event::KeyPressed) {
		if (e.key.code == sf::Keyboard::Return) {
			select(m_currentSelection);
		}
		if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W) {
			m_currentSelection--;
			if (m_currentSelection < 1) {
				//hardcoding
				m_currentSelection = 3;
			}
		}
		if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S) {
			m_currentSelection++;
			//hardcoding this size, sizeof(options) doesnt work...
			if (m_currentSelection == 4) {
				m_currentSelection = 1;
			}
		}
	}
}

void  MenuState::select(int m_currentSelection) {
	//figure out what to do if m_currentSelection == 3 (quitState)
	gsm->setState(m_currentSelection);
}

void MenuState::update() {

}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Text text;
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
	text.setFont(font);
	int x = 50;
	int y = 50;
	//hardcoding
	for(int i = 1; i < 4; i++) {
		text.setPosition(x, y);
		text.setString(options[i]);
		if (i == m_currentSelection) {
			text.setFillColor(sf::Color::Red);
		} else {
			text.setFillColor(sf::Color::White);
		}
		target.draw(text);
		y += 50;
	}
}