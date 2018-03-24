#include "Physics.h"
#include "StateManager.h"

void rotatePoint(sf::Vector3f &point, float angle, int dim) {
	if (dim == 0) {
		//around x-axis
		float newY = point.y*cos(angle) - point.z*sin(angle);
		point.z = point.y*sin(angle) + point.z*cos(angle);
		point.y = newY;
	}
	else if (dim == 1) {
		//around y-axis
		float newX = point.x*cos(angle) + point.z*sin(angle);
		point.z = -point.x*sin(angle) + point.z*cos(angle);
		point.x = newX;
	}
	else if (dim == 2) {
		//around z-axis
		float newX = point.x*cos(angle) - point.y*sin(angle);
		point.y = point.x*sin(angle) + point.y*cos(angle);
		point.x = newX;
	}
}

void Physics::rotateCam(float angle, int dim) {
	if (dim == 0) {
		//around x-axis
		
	}
	else if (dim == 1) {
		//around y-axis
		m_cameraPhi += angle;
	}
	else if (dim == 2) {
		//around z-axis
		m_cameraTheta += angle;
	}
}

void translatePoint(sf::Vector3f &point,float x, float y, float z) {
	point.x = point.x + x;
	point.y = point.y + y;
	point.z = point.z + z;
}

void Physics::translateCam(float x, float y, float z) {
	m_cameraPos.x += x;
	m_cameraPos.y += y;
	m_cameraPos.z += z;
}

void Physics::prepVisual() {
	//do calculations and set visual objects position
}

Physics::Physics(StateManager* sm) {
	m_stateManager = sm;
}

Physics::~Physics() {

}

void Physics::update() {

}

void Physics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_objVisual);
}

void Physics::handleEvent(const sf::Event &e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A) {
			//strafe left
		}
		else if (e.key.code == sf::Keyboard::D) {
			//strafe right
		}
		else if (e.key.code == sf::Keyboard::W) {
			//forward
			translateCam(m_cameraSpeed, 0.f, 0.f);
		}
		else if (e.key.code == sf::Keyboard::S) {
			//backward
			translateCam(-m_cameraSpeed, 0.f, 0.f);
		}
		else if (e.key.code == sf::Keyboard::Escape) {
			queueSwitch(MENUSTATE);
		}
		break;

	}
	
}