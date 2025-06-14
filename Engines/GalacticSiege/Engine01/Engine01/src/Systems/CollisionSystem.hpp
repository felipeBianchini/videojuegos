#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <memory>

#include "../ECS/ECS.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @class CollisionSystem
 * @brief A system for detecting collisions between entities in an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with CircleColliderComponent and TransformComponent, checking for circular
 * collisions between pairs of entities and emitting CollisionEvent notifications when collisions occur.
 */
class CollisionSystem : public System {
public:
	/**
	 * @brief Constructor for the CollisionSystem.
	 *
	 * Initializes the system and specifies that entities must have CircleColliderComponent and
	 * TransformComponent to be managed.
	 */
	CollisionSystem() {
		RequiredComponent<CircleColliderComponent>();
		RequiredComponent<TransformComponent>();
	}
	/**
	 * @brief Updates the system by checking for collisions between entities.
	 *
	 * Iterates through all pairs of managed entities, calculates their collision boundaries based on
	 * their positions and collider radii, and emits a CollisionEvent if a collision is detected.
	 *
	 * @param eventManager A unique pointer to the EventManager for emitting collision events.
	 */
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

				glm::vec2 aCenterPos = glm::vec2(
					aTransform.position.x + (aCollider.width / 2.0f) * aTransform.scale.x,
					aTransform.position.y + (aCollider.height / 2.0f) * aTransform.scale.y
				);

				glm::vec2 bCenterPos = glm::vec2(
					bTransform.position.x + (bCollider.width / 2.0f) * bTransform.scale.x,
					bTransform.position.y + (bCollider.height / 2.0f) * bTransform.scale.y
				);


				int aRadius = aCollider.radius * glm::max(aTransform.scale.x, aTransform.scale.y);
				int bRadius = bCollider.radius * glm::max(bTransform.scale.x, bTransform.scale.y);

				bool collision = CheckCircularCollision(aRadius, bRadius, aCenterPos, bCenterPos);

				if (collision) {
					eventManager->EmitEvent<CollisionEvent>(a, b);
				}
			}
		}
	}
	/**
	 * @brief Checks for circular collision between two entities.
	 *
	 * Determines if two entities collide by comparing the distance between their centers to the sum
	 * of their radii.
	 *
	 * @param aRadius The collision radius of the first entity.
	 * @param bRadius The collision radius of the second entity.
	 * @param aPos The center position of the first entity.
	 * @param bPos The center position of the second entity.
	 * @return True if the entities collide, false otherwise.
	 */
	bool CheckCircularCollision(int aRadius, int bRadius, glm::vec2 aPos, glm::vec2 bPos) {
		glm::vec2 dif = aPos - bPos;
		double length = glm::sqrt((dif.x * dif.x) + (dif.y * dif.y));
		// Hay colisión si la suma de los radios es mayor a la distancia entre centros
		return (aRadius + bRadius) >= length;
	}
};

#endif // !COLLISIONSYSTEM_HPP
