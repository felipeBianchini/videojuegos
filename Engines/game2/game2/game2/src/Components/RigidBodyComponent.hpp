#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent {
	bool isDynamic;
	float mass;
	float invMass;
	glm::vec2 velocity = glm::vec2(0);
	glm::vec2 acceleration = glm::vec2(0);
	glm::vec2 sumForces = glm::vec2(0);
	RigidBodyComponent(bool isDynamic = false, float mass = 1) {
		this->isDynamic = isDynamic;
		this->mass = mass;
		this->invMass = 1 / mass;
	}
};

#endif // RIGIDBODYCOMPONENT_HPP