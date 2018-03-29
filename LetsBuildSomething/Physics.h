#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H
//PHYSICS GAME PogChamp
#include "Game.h"

//here we will try out our fake 3d rendering

class Physics : public Game {
	//looks like the preferred way to do this is store a camera matrix and view matrix; where camera matrix is the result of user input
	//and view matrix is the "opposite" that will be applied to an object
	sf::Vector3f m_cameraPos{0.f,0.f,0.f};
	float m_cameraTheta = 0.f;
	float m_cameraPhi = 3.1415926/2.f;
	float m_cameraYaw = 0.f;
	float m_cameraSpeed = 20.f;
	float m_windowDistance = 20.f;
	float m_windowW = 800.f;
	float m_windowH = 800.f;

	bool m_canDraw = 0;

	sf::Vector3f m_pointPos{ 100.f, 0.f, 0.f };
	sf::RectangleShape m_objVisual{ sf::Vector2f(50.f, 50.f) };

	void rotateCam(float angle, int dim);
	void translateCam(float x, float y, float z);
	bool prepVisual();

public:
	Physics(StateManager *);

	~Physics();

	void update();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void handleEvent(const sf::Event &e);
};



#endif // !PHYSICS_H
