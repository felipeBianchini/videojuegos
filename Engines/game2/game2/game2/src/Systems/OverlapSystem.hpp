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

enum Direction {top, left, bottom, right};

class OverlapSystem : public System {
private:
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
	OverlapSystem() {
		RequiredComponent<BoxColliderComponent>();
		RequiredComponent<RigidBodyComponent>();
		RequiredComponent<TransformComponent>();
	}

	void SubscribeToCollisionEvent(const std::unique_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<CollisionEvent, OverlapSystem>(this, &OverlapSystem::OnCollisionEvent);
	}

	void OnCollisionEvent(CollisionEvent& e) {
		auto& aRigidbody = e.a.GetComponent<RigidBodyComponent>();
		auto& bRigidbody = e.b.GetComponent<RigidBodyComponent>();
		if (e.a.HasComponent<TagComponent>()) {
			if (e.a.GetComponent<TagComponent>().tag.find("door") != std::string::npos) {
				return;
			}
		}
		if (e.b.HasComponent<TagComponent>()) {
			if (e.b.GetComponent<TagComponent>().tag.find("door") != std::string::npos) {
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