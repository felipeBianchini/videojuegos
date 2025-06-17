#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <tuple>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

// Controles

bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// RigidBodyComponent

void SetVelocity(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.velocity.x = x;
	rigidBody.velocity.y = y;
}

std::tuple<int, int> GetVelocity(Entity entity) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	return {
		static_cast<int>(rigidBody.velocity.x),
		static_cast<int>(rigidBody.velocity.y)
	};
}

void GoToScene(const std::string& sceneName) {
	Game::GetInstance().sceneManager->SetNextScene(sceneName);
	Game::GetInstance().sceneManager->StopScene();
}

std::string GetTag(Entity entity) {
	return entity.GetComponent<TagComponent>().tag;
}

bool LeftCollision(Entity e, Entity other) {
	const auto& eCollider = e.GetComponent<BoxColliderComponent>();
	const auto& eTransform = e.GetComponent<TransformComponent>();
	const auto& otherCollider = other.GetComponent<BoxColliderComponent>();
	const auto& otherTransform = other.GetComponent<TransformComponent>();
	float eX = eTransform.previousPosition.x;
	float eY = eTransform.previousPosition.y;
	float eH = static_cast<float>(eCollider.heigth);
	float oX = otherTransform.previousPosition.x;
	float oY = otherTransform.previousPosition.y;
	float oH = static_cast<float>(otherCollider.heigth);
	return (
		oY < eY + eH &&
		oY + oH > eY &&
		oX < eX
	);

}

bool RightCollision(Entity e, Entity other) {
	const auto& eCollider = e.GetComponent<BoxColliderComponent>();
	const auto& eTransform = e.GetComponent<TransformComponent>();
	const auto& otherCollider = other.GetComponent<BoxColliderComponent>();
	const auto& otherTransform = other.GetComponent<TransformComponent>();
	float eX = eTransform.previousPosition.x;
	float eY = eTransform.previousPosition.y;
	float eH = static_cast<float>(eCollider.heigth);
	float oX = otherTransform.previousPosition.x;
	float oY = otherTransform.previousPosition.y;
	float oH = static_cast<float>(otherCollider.heigth);
	return (
		oY < eY + eH &&
		oY + oH > eY &&
		oX > eX
		);
}

std::tuple<int, int> GetPosition(Entity entity) {
	const auto& transform = entity.GetComponent<TransformComponent>();
	return {
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y)
	};
}

void SetPosition(Entity entity, int x, int y) {
	auto& transform = entity.GetComponent<TransformComponent>();
	transform.position.x = x;
	transform.position.y;
}

std::tuple<int, int> GetSize(Entity entity) {
	const auto& sprite = entity.GetComponent<SpriteComponent>();
	const auto& transform = entity.GetComponent<TransformComponent>();
	int width = sprite.width * transform.scale.x;
	int heigth = sprite.height * transform.scale.y;
	return { width, heigth };
}

#endif // !LUABINDING_HPP