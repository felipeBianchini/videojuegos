#ifndef PHYSICSYSTEM_HPP
#define PHYSICSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../ECS/ECS.hpp"

class PhysicsSystem : public System {
public:
	PhysicsSystem() {
		RequiredComponent<RigidBodyComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntiities()) {
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();
			if (rigidbody.isDynamic) {
				rigidbody.sumForces += glm::vec2(0.0f, 9.8 * rigidbody.mass * 64);
			}
		}
	}
};

#endif // !PHYSICSYSTEM_HPP