#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include <glm/glm.hpp>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequiredComponent<RigidBodyComponent>();
		RequiredComponent<TransformComponent>();
	}

	void Update(double dt) {
		for (auto entity : GetSystemEntiities()) {
			auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			transform.previousPosition = transform.position;
			
			if (rigidBody.isDynamic) {
				rigidBody.acceleration = rigidBody.sumForces * rigidBody.invMass;
				rigidBody.velocity += rigidBody.acceleration * static_cast<float>(dt);
				transform.position += rigidBody.velocity * static_cast<float>(dt);
				rigidBody.sumForces = glm::vec2(0);
			}
			else {
				transform.position.x += rigidBody.velocity.x * dt;
				transform.position.y += rigidBody.velocity.y * dt;
			}
		}
	}
};

#endif // MOVEMENTSYSTEM_HPP