#include "Physics.h"
#include "StateManager.h"

//should make this a template probs, but thats for another day
float dotProduct(std::array<float, 4> &vec1, std::array<float, 4> &vec2) {
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2] + vec1[3] * vec2[3];
}

void vectorTrans(std::array<float, 16> &mat, std::array<float, 4> &vec) {
	std::array<float, 4> output;
	for (int i = 0; i < 4; i++) {
		std::array<float, 4> matRow = { mat[4 * i], mat[1 + 4 * i], mat[2 + 4 * i], mat[3 + 4 * i] };
		output[i] = dotProduct(matRow, vec);
	}
	vec = output;
}

void matrixMultiply(std::array<float, 16> &mat1, std::array<float, 16> &mat2) {
	std::array<float, 16> output;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::array<float, 4> matRow = { mat1[4 * i],mat1[1 + 4 * i],mat1[2 + 4 * i],mat1[3 + 4 * i] };
			std::array<float, 4> matCol = { mat2[j],mat2[j + 4],mat2[j + 8] ,mat2[j + 12] };
			output[j + 4 * i] = dotProduct(matRow, matCol);
		}
	}
	mat2 = output;
}

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
		if (m_cameraPhi + angle < 0) {
			//check if change would cross 0
			angle = -m_cameraPhi;
			m_cameraPhi = 0;
		}
		else if (m_cameraPhi + angle > 3.1415926) {
			//check if change would cross pi
			angle = 3.1415926 - m_cameraPhi;
			m_cameraPhi = 3.1415926;
		}
		else {
			m_cameraPhi += angle;
		}
		std::array<float, 16> rotMat = { cos(-angle), -sin(-angle), 0, 0, sin(-angle), cos(-angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		matrixMultiply(rotMat, m_viewMatrix);
	}
	else if (dim == 2) {
		//around z-axis
		std::array<float, 16> rotMat = { cos(-angle), 0, sin(-angle), 0, 0, 1, 0, 0, -sin(-angle), 0, cos(-angle), 0, 0, 0, 0, 1 };
		matrixMultiply(rotMat, m_viewMatrix);
	}
}

void translatePoint(sf::Vector3f &point,float x, float y, float z) {
	point.x = point.x + x;
	point.y = point.y + y;
	point.z = point.z + z;
}

void Physics::translateCam(float x, float y, float z) {
	std::array<float, 16> transMat = { 1, 0, 0, -x, 0, 1, 0, -y, 0, 0, 1, -z, 0, 0, 0, 1 };
	matrixMultiply(transMat, m_viewMatrix);
}

bool Physics::prepVisual() {
	//do calculations and set visual objects position
	std::array<float, 4> visualPos = {m_pointPos.x, m_pointPos.y, m_pointPos.z, 1};
	vectorTrans(m_viewMatrix, visualPos);
	std::cout << "Obj position: (" << visualPos[0] << ", " << visualPos[1] << ", " << visualPos[2] << ")" << std::endl;
	if (m_windowDistance < visualPos[0]) {
		//ratio = screen distance / visualP dotted with screenplane / screen distance -> simplifies to
		//screenDistance/x of visualP
		float ratio = m_windowDistance/visualPos[0];
		//ratio * visualPos gives projection
		m_objVisual.setPosition(sf::Vector2f(visualPos[2] * ratio + 350, visualPos[1] * ratio + 350));
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
	//std::cout << "Camera Position: (" << m_cameraPos.x << ", " << m_cameraPos.y << ", " << m_cameraPos.z << ")" << std::endl;
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
			translateCam(m_cameraSpeed*sin(m_cameraTheta), 0.f, -m_cameraSpeed*cos(m_cameraTheta));
			//strafe left
		}
		else if (e.key.code == sf::Keyboard::D) {
			//strafe right
			translateCam(-m_cameraSpeed*sin(m_cameraTheta), 0.f, m_cameraSpeed*cos(m_cameraTheta));
		}
		else if (e.key.code == sf::Keyboard::W) {
			//forward
			translateCam(m_cameraSpeed*sin(m_cameraPhi)*cos(m_cameraTheta), m_cameraSpeed*cos(m_cameraPhi), m_cameraSpeed*sin(m_cameraPhi)*sin(m_cameraTheta));
		}
		else if (e.key.code == sf::Keyboard::S) {
			//backward
			translateCam(-m_cameraSpeed*sin(m_cameraPhi)*cos(m_cameraTheta), -m_cameraSpeed*cos(m_cameraPhi), -m_cameraSpeed * sin(m_cameraPhi)*sin(m_cameraTheta));
		}
		else if (e.key.code == sf::Keyboard::Escape) {
			queueSwitch(MENUSTATE);
		}
		else if (e.key.code == sf::Keyboard::Up) {
			//look down
			rotateCam(-10.f * 3.1415926 / 180.f, 1);
		}
		else if (e.key.code == sf::Keyboard::Down) {
			//look up
			rotateCam(10.f * 3.1415926 / 180.f, 1);
		}
		else if (e.key.code == sf::Keyboard::Left) {
			//turn left
			rotateCam(10.f*3.1415926 / 180.f, 2);
		}
		else if (e.key.code == sf::Keyboard::Right) {
			rotateCam(-10.f*3.1415926 / 180.f, 2);
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