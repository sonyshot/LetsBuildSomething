#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H
//PHYSICS GAME PogChamp
#include "Game.h"

//here we will try out our fake 3d rendering

class Physics : public Game {
	sf::Vector3f m_cameraPos{0.f,0.f,0.f};
	float m_cameraTheta = 0.f;
	float m_cameraPhi = 0.f;
	float m_cameraYaw = 0.f;
	float m_cameraSpeed = 20.f;
	float m_windowDistance = 10.f;
	float m_windowW = 800.f;
	float m_windowH = 800.f;

	sf::Vector3f m_pointPos{ 100.f, 25.f, 25.f };
	sf::RectangleShape m_objVisual{ sf::Vector2f(10.f, 10.f) };

	void rotateCam(float angle, int dim);
	void translateCam(float x, float y, float z);
	void prepVisual();

public:
	Physics(StateManager *);

	~Physics();

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);
};



#endif // !PHYSICS_H
