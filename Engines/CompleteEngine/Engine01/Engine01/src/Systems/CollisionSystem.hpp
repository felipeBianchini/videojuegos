#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

class CollisionSystem : public System {
public:
	CollisionSystem() {
		RequiredComponent<CircleColliderComponent>();
		RequiredComponent<TransformComponent>();
	}

	void Update(std::unique_ptr<EventManager>& eventManager) {
		auto entities = GetSystemEntiities();
		for (auto i = entities.begin(); i != entities.end(); ++i) {
			Entity a = *i;
			if (!a.IsAlive() || !a.HasComponent<CircleColliderComponent>() || !a.HasComponent<TransformComponent>()) {
				continue;
			}
			auto& aCollider = a.GetComponent<CircleColliderComponent>();
			auto& aTransform = a.GetComponent<TransformComponent>();

			for (auto j = std::next(i); j != entities.end(); ++j) {
				Entity b = *j;
				if (!b.IsAlive() || !b.HasComponent<CircleColliderComponent>() || !b.HasComponent<TransformComponent>()) {
					continue;
				}
				auto& bCollider = b.GetComponent<CircleColliderComponent>();
				auto& bTransform = b.GetComponent<TransformComponent>();

				glm::vec2 aCenterPos = glm::vec2(aTransform.position.x, aTransform.position.y);
				glm::vec2 bCenterPos = glm::vec2(bTransform.position.x, bTransform.position.y);

				int aRadius = aCollider.radius * glm::max(aTransform.scale.x, aTransform.scale.y);
				int bRadius = bCollider.radius * glm::max(bTransform.scale.x, bTransform.scale.y);

				bool collision = CheckCircularCollision(aRadius, bRadius, aCenterPos, bCenterPos);

				if (collision) {
					eventManager->EmitEvent<CollisionEvent>(a, b);
				}
			}
		}
	}

	bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos, glm::vec2 bPos) {
		glm::vec2 dif = aPos - bPos;
		double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
		// Hay colisión si la suma de los radios es mayor a la distancia entre centros
		return (aRadius + bRadius) >= length;
	}
};

#endif // !COLLISIONSYSTEM_HPP
