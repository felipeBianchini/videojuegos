#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequiredComponent<CircleColliderComponent>();
		RequiredComponent<TransformComponent>();
	}

	void Update() {
		auto entities = GetSystemEntiities();
		for (auto i = entities.begin(); i != entities.end(); i++) {
			Entity a = *i;
			auto aCollider = a.GetComponent<CircleColliderComponent>();
			auto aTranform = a.GetComponent<TransformComponent>();
			for (auto j = i; j != entities.end(); j++) {
				Entity b = *j;
				if (a == b) {
					continue;
				}

				auto bCollider = b.GetComponent<CircleColliderComponent>();
				auto bTranform = b.GetComponent<TransformComponent>();

				bool collision = CheckCircularCollision();

				if (collision) {

				}
			}
		}
	}

	bool CheckCircularCollision() {

	}
};

#endif // !COLLISIONSYSTEM_HPP