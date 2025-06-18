#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent {
	bool isDynamic;
	bool isSolid;
	float mass;
	float invMass;
	glm::vec2 velocity = glm::vec2(0);
	glm::vec2 acceleration = glm::vec2(0);
	glm::vec2 sumForces = glm::vec2(0);
	RigidBodyComponent(bool isDynamic = false, bool isSolid = false, float mass = 1) {
		this->isDynamic = isDynamic;
		this->mass = mass;
		this->invMass = 1 / mass;
		this->isSolid = isSolid;
	}
};

#endif // RIGIDBODYCOMPONENT_HPP