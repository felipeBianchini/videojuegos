#ifndef BOXCOLLIDERCOMPONENT_HPP
#define BOXCOLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>

struct BoxColliderComponent {
	int width;
	int heigth;
	glm::vec2 offset;

	BoxColliderComponent(int width = 0, int heigth = 0, glm::vec2 offset = glm::vec2(0)) {
		this->width = width;
		this->heigth = heigth;
		this->offset = offset;
	}
};

#endif // !BOXCOLLIDERCOMPONENT_HPP
