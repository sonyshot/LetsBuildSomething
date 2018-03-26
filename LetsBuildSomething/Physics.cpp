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

bool Physics::prepVisual() {
	//do calculations and set visual objects position
	sf::Vector3f visualPos(m_pointPos);
	rotatePoint(visualPos, -m_cameraPhi, 1);
	rotatePoint(visualPos, -m_cameraTheta, 2);
	translatePoint(visualPos, -m_cameraPos.x, -m_cameraPos.y, -m_cameraPos.z);
	sf::Vector3f screenPlane({m_cameraPos.x + m_windowDistance *(cos(m_cameraTheta)*sin(m_cameraPhi)), m_cameraPos.y + m_windowDistance * (sin(m_cameraTheta)*sin(m_cameraPhi)), m_cameraPos.z + m_windowDistance * (cos(m_cameraPhi))  });
	if (m_windowDistance*m_windowDistance - visualPos.x*screenPlane.x - visualPos.y*screenPlane.y - visualPos.z*screenPlane.z) {
		//point is above the plane return calcualte projection, check that its in the window, return true
		float posDis = sqrt(visualPos.x*visualPos.x + visualPos.y*visualPos.y + visualPos.z*visualPos.z);
		//ratio = screen distance / visualP dotted with screenplane / screen distance
		float ratio = m_windowDistance * m_windowDistance / (visualPos.x*screenPlane.x + visualPos.y*screenPlane.y + visualPos.z*screenPlane.z);
		//ratio * visualPos gives projection
		m_objVisual.setPosition(sf::Vector2f(visualPos.x * ratio + 350, visualPos.z * ratio + 350));
		return true;
	}
	return false;
}

Physics::Physics(StateManager* sm) {
	m_objVisual.setFillColor(sf::Color::White);

	m_stateManager = sm;
}

Physics::~Physics() {

}

void Physics::update() {
	m_canDraw = prepVisual();
}

void Physics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (m_canDraw) {
		target.draw(m_objVisual);
	}
}

void Physics::handleEvent(const sf::Event &e) {
	switch (e.type) {
	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::A) {
			translateCam(0.f, -m_cameraSpeed, 0.f);
			//strafe left
		}
		else if (e.key.code == sf::Keyboard::D) {
			//strafe right
			translateCam(0.f, m_cameraSpeed, 0.f);
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
		else if (e.key.code == sf::Keyboard::Up) {
			//look down
			m_cameraPhi += 10.f*3.1415926/180.f;
			if (m_cameraPhi > 3.1415926)
				m_cameraPhi = 3.1415926;
		}
		else if (e.key.code == sf::Keyboard::Down) {
			//look up
			m_cameraPhi -= 10.f*3.1415926 / 180.f;
			if (m_cameraPhi < 0)
				m_cameraPhi = 0;
		}
		else if (e.key.code == sf::Keyboard::Left) {
			//turn left
			m_cameraTheta -= 10.f*3.1415926 / 180.f;
		}
		else if (e.key.code == sf::Keyboard::Right) {
			m_cameraTheta += 10.f*3.1415926 / 180.f;
		}
		break;

	/*case sf::Event::MouseMoved:
		std::cout << "new mouse x: " << e.mouseMove.x << std::endl;
		std::cout << "new mouse y: " << e.mouseMove.y << std::endl;
		m_cameraTheta += 10*(e.mouseMove.x - 900);
		m_cameraPhi += 10*(e.mouseMove.y - 500);
		break;
	*/
	}
	
}