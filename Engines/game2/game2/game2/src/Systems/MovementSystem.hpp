#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

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
			const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			transform.previousPosition = transform.position;
			transform.position.x += rigidBody.velocity.x * dt;
			transform.position.y += rigidBody.velocity.y * dt;
		}
	}
};

#endif // MOVEMENTSYSTEM_HPP