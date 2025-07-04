/**
 * @file OverlapSystem.hpp
 * @brief Defines the OverlapSystem class for handling collision resolution and overlap prevention
 */

#ifndef OVERLAPSYSTEM_HPP
#define OVERLAPSYSTEM_HPP

#include <memory>
#include <string>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/CollisionEvent.hpp"

/**
 * @enum Direction
 * @brief Enumeration for collision directions
 */
enum Direction {top, left, bottom, right};

/**
 * @class OverlapSystem
 * @brief System responsible for resolving collisions and preventing entity overlap
 * 
 * This system processes entities with BoxColliderComponent, RigidBodyComponent, and TransformComponent,
 * handling collision resolution by repositioning entities and adjusting their velocities to prevent overlap.
 */
class OverlapSystem : public System {
private:
    /**
     * @brief Checks if two entities are colliding from a specific direction
     * 
     * Performs directional collision detection between two box colliders using their
     * previous positions to determine collision direction.
     * 
     * @param a First entity to check collision for
     * @param b Second entity to check collision against
     * @param dir Direction to check collision from (top, bottom, left, right)
     * @return true if collision is detected from the specified direction, false otherwise
     */
	bool CheckCollision(Entity a, Entity b, Direction dir) {
		auto& aCollider = a.GetComponent<BoxColliderComponent>();
		auto& bCollider = b.GetComponent<BoxColliderComponent>();
		auto& aTransform = a.GetComponent<TransformComponent>();
		auto& bTransform = b.GetComponent<TransformComponent>();
		
		float aX = aTransform.previousPosition.x;
		float aY = aTransform.previousPosition.y;
		float aW = static_cast<float>(aCollider.width);
		float aH = static_cast<float>(aCollider.heigth);

		float bX = bTransform.previousPosition.x;
		float bY = bTransform.previousPosition.y;
		float bW = static_cast<float>(bCollider.width);
		float bH = static_cast<float>(bCollider.heigth);
	
		if (Direction::top == dir) {
			return (
				aX < bX + bW &&
				aX + aW > bX &&
				aY > bY
				);
		} else if (Direction::bottom == dir) {
			return (
				aX < bX + bW &&
				aX + aW > bX &&
				aY < bY
				);
		} else if (Direction::left == dir) {
			return (
				aY < bY + bH &&
				aY + aH > bY &&
				aX > bX
				);
		} else if (Direction::right == dir) {
			return (
				aY < bY + bH &&
				aY + aH > bY &&
				aX < bX
				);
		}
		else {
			return false;
		}

	}

    /**
     * @brief Resolves collision overlap between two entities
     * 
     * Repositions the second entity to avoid overlap with the first entity and
     * adjusts its velocity based on the collision direction.
     * 
     * @param a Reference entity (stationary)
     * @param b Entity to be repositioned to avoid overlap
     */
	void AvoidOverlap(Entity a, Entity b) {
		auto& aCollider = a.GetComponent<BoxColliderComponent>();
		auto& aTransform = a.GetComponent<TransformComponent>();
		auto& bCollider = b.GetComponent<BoxColliderComponent>();
		auto& bTransform = b.GetComponent<TransformComponent>();
		auto& bRigidbody = b.GetComponent<RigidBodyComponent>();
		if (CheckCollision(a, b, Direction::top)) {
			bTransform.position = glm::vec2(bTransform.position.x,
				aTransform.position.y - bCollider.heigth);
			bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
		}
		else if (CheckCollision(a, b, Direction::bottom)) {
			bTransform.position = glm::vec2(bTransform.position.x,
				aTransform.position.y + aCollider.heigth);
			bRigidbody.velocity = glm::vec2(bRigidbody.velocity.x, 0.0f);
		}
		else if (CheckCollision(a, b, Direction::right)) {
			bTransform.position = glm::vec2(aTransform.position.x + aCollider.width,
				bTransform.position.y);
			bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
		}
		else if (CheckCollision(a, b, Direction::left)) {
			bTransform.position = glm::vec2(aTransform.position.x - bCollider.width,
				bTransform.position.y);
			bRigidbody.velocity = glm::vec2(0.0f, bRigidbody.velocity.y);
		}
	}
public:
    /**
     * @brief Constructor for OverlapSystem
     * 
     * Sets up the required components for this system: BoxColliderComponent,
     * RigidBodyComponent, and TransformComponent
     */
	OverlapSystem() {
		RequiredComponent<BoxColliderComponent>();
		RequiredComponent<RigidBodyComponent>();
		RequiredComponent<TransformComponent>();
	}

    /**
     * @brief Subscribes this system to collision events
     * 
     * Registers the OnCollisionEvent method as a callback for CollisionEvent,
     * allowing the system to respond when collisions occur.
     * 
     * @param eventManager Unique pointer to the event manager for subscribing to events
     */
	void SubscribeToCollisionEvent(const std::unique_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnCollisionEvent);
	}

    /**
     * @brief Handles collision events and resolves overlaps
     * 
     * Called when a collision event is triggered. Checks for special entity tags
     * (door, jumpable, slowdown) to skip collision resolution, then resolves
     * overlaps between solid entities based on their mass properties.
     * 
     * @param e Reference to the collision event containing the two colliding entities
     */
	void OnCollisionEvent(CollisionEvent& e) {
		auto& aRigidbody = e.a.GetComponent<RigidBodyComponent>();
		auto& bRigidbody = e.b.GetComponent<RigidBodyComponent>();
		if (e.a.HasComponent<TagComponent>()) {
			if (e.a.GetComponent<TagComponent>().tag.find("door") != std::string::npos ||
				e.a.GetComponent<TagComponent>().tag.find("jumpable") != std::string::npos ||
				e.a.GetComponent<TagComponent>().tag.find("slowdown") != std::string::npos) {
				return;
			}
		}
		if (e.b.HasComponent<TagComponent>()) {
			if (e.b.GetComponent<TagComponent>().tag.find("door") != std::string::npos ||
				e.b.GetComponent<TagComponent>().tag.find("jumpable") != std::string::npos ||
				e.b.GetComponent<TagComponent>().tag.find("slowdown") != std::string::npos) {
				return;
			}
		}
		if (aRigidbody.isSolid && bRigidbody.isSolid) {
			if (aRigidbody.mass >= bRigidbody.mass) {
				AvoidOverlap(e.a, e.b);
			}
			else {
				AvoidOverlap(e.b, e.a);
			}
		}
	}
};

#endif // !OVERLAPSYSTEM_HPP