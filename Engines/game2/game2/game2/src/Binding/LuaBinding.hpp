/**
 * @file LuaBinding.hpp
 * @brief Lua binding functions for game scripting system
 */

#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <tuple>
#include <SDL2/SDL.h>

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../AnimationManager/AnimationManager.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

// Controles

/**
 * @brief Checks if a specific action is currently activated
 * @param action The name of the action to check
 * @return true if the action is activated, false otherwise
 */
bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
}

// RigidBodyComponent

/**
 * @brief Sets the velocity of an entity's rigid body
 * @param entity The entity to modify
 * @param x The velocity in the x-axis
 * @param y The velocity in the y-axis
 */
void SetVelocity(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.velocity.x = x;
	rigidBody.velocity.y = y;
}

/**
 * @brief Gets the velocity of an entity's rigid body
 * @param entity The entity to query
 * @return A tuple containing the x and y velocity components as integers
 */
std::tuple<int, int> GetVelocity(Entity entity) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	return {
		static_cast<int>(rigidBody.velocity.x),
		static_cast<int>(rigidBody.velocity.y)
	};
}

/**
 * @brief Transitions to a new scene
 * @param sceneName The name of the scene to transition to
 */
void GoToScene(const std::string& sceneName) {
	Game::GetInstance().sceneManager->SetNextScene(sceneName);
	Game::GetInstance().sceneManager->StopScene();
}

/**
 * @brief Gets the tag of an entity
 * @param entity The entity to query
 * @return The tag string of the entity
 */
std::string GetTag(Entity entity) {
	return entity.GetComponent<TagComponent>().tag;
}

/**
 * @brief Checks if a collision occurred on the left side of an entity
 * @param e The primary entity
 * @param other The other entity involved in the collision
 * @return true if the collision is on the left side, false otherwise
 */
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

/**
 * @brief Checks if a collision occurred on the right side of an entity
 * @param e The primary entity
 * @param other The other entity involved in the collision
 * @return true if the collision is on the right side, false otherwise
 */
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

/**
 * @brief Checks if a collision occurred on the bottom side of an entity
 * @param e The primary entity
 * @param other The other entity involved in the collision
 * @return true if the collision is on the bottom side, false otherwise
 */
bool BottomCollision(Entity e, Entity other) {
	const auto& eCollider = e.GetComponent<BoxColliderComponent>();
	const auto& eTransform = e.GetComponent<TransformComponent>();
	const auto& otherCollider = other.GetComponent<BoxColliderComponent>();
	const auto& otherTransform = other.GetComponent<TransformComponent>();

	float eX = eTransform.previousPosition.x;
	float eY = eTransform.previousPosition.y;
	float eW = static_cast<float>(eCollider.width);

	float oX = otherTransform.previousPosition.x;
	float oY = otherTransform.previousPosition.y;
	float oW = static_cast<float>(otherCollider.width);

	return (
		oX < eX + eW &&
		oX + oW > eX &&
		oY > eY
		);
}

/**
 * @brief Checks if a collision occurred on the top side of an entity
 * @param e The primary entity
 * @param other The other entity involved in the collision
 * @return true if the collision is on the top side, false otherwise
 */
bool TopCollision(Entity e, Entity other) {
	const auto& eCollider = e.GetComponent<BoxColliderComponent>();
	const auto& eTransform = e.GetComponent<TransformComponent>();
	const auto& otherCollider = other.GetComponent<BoxColliderComponent>();
	const auto& otherTransform = other.GetComponent<TransformComponent>();

	float eX = eTransform.previousPosition.x;
	float eY = eTransform.previousPosition.y;
	float eW = static_cast<float>(eCollider.width);

	float oX = otherTransform.previousPosition.x;
	float oY = otherTransform.previousPosition.y;
	float oW = static_cast<float>(otherCollider.width);
	float oH = static_cast<float>(otherCollider.heigth);

	return (
		oX < eX + eW &&
		oX + oW > eX &&
		oY + oH < eY
		);
}

/**
 * @brief Gets the position of an entity
 * @param entity The entity to query
 * @return A tuple containing the x and y position coordinates as integers
 */
std::tuple<int, int> GetPosition(Entity entity) {
	const auto& transform = entity.GetComponent<TransformComponent>();
	return {
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y)
	};
}

/**
 * @brief Sets the position of an entity
 * @param entity The entity to modify
 * @param x The new x-coordinate
 * @param y The new y-coordinate
 */
void SetPosition(Entity entity, float x, float y) {
	auto& transform = entity.GetComponent<TransformComponent>();
	transform.position.x = x;
	transform.position.y = y;
}

/**
 * @brief Gets the scaled size of an entity
 * @param entity The entity to query
 * @return A tuple containing the scaled width and height as integers
 */
std::tuple<int, int> GetSize(Entity entity) {
	const auto& sprite = entity.GetComponent<SpriteComponent>();
	const auto& transform = entity.GetComponent<TransformComponent>();
	int width = sprite.width * transform.scale.x;
	int heigth = sprite.height * transform.scale.y;
	return { width, heigth };
}

/**
 * @brief Adds a force to an entity's rigid body
 * @param entity The entity to apply force to
 * @param x The force in the x-axis
 * @param y The force in the y-axis
 */
void AddForce(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.sumForces += glm::vec2(x, y);
}

/**
 * @brief Changes the animation of an entity
 * @param entity The entity to modify
 * @param animationId The identifier of the animation to change to
 */
void ChangeAnimation(Entity entity, const std::string& animationId) {
	auto& animation = entity.GetComponent<AnimationComponent>();
	auto& sprite = entity.GetComponent<SpriteComponent>();
	AnimationData animationData;
	animationData = Game::GetInstance().animationManager->GetAnimation(animationId);
	sprite.textureId = animationData.textureId;
	sprite.width = animationData.width;
	sprite.height = animationData.height;
	sprite.srcRect.x = 0;
	sprite.srcRect.y = 0;
	animation.currentFrame = 1;
	animation.frameSpeedRate = animationData.frameSpeedRate;
	animation.numFrames = animationData.numFrames;
	animation.isLoop = animationData.isLoop;
	animation.startTime = SDL_GetTicks();
}

/**
 * @brief Flips the sprite of an entity horizontally
 * @param entity The entity to modify
 * @param flip true to flip the sprite, false to restore normal orientation
 */
void FlipSprite(Entity entity, bool flip) {
	auto& sprite = entity.GetComponent<SpriteComponent>();
	sprite.flip = flip;
}

/**
 * @brief Plays a sound effect with specified volume
 * @param soundEffectId The identifier of the sound effect to play
 * @param volume The volume level (0-128)
 */
void PlaySoundEffect(const std::string& soundEffectId, int volume) {
	Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
	if (soundEffect) {
		Mix_VolumeChunk(soundEffect, volume);
		Mix_PlayChannel(-1, soundEffect, 0);
	}
}

/**
 * @brief Marks an entity for destruction
 * @param entity The entity to kill
 */
void KillEntity(Entity entity) {
	entity.Kill();
}

/**
 * @brief Handles player death event
 * 
 * Sets the game restart flag, increments death counter, and logs the event.
 */
void PlayerKilled() {
	Game::GetInstance().isRestarting = true;
	Game::GetInstance().currentDeaths ++;
	std::cout << "[LuaBinding] Player killed!\n";
}

/**
 * @brief Transitions to the next level in the game sequence
 * 
 * Determines the current level and advances to the next one in the sequence.
 * If at the final level, returns to the main menu.
 */
void NextLevel() {
	std::string currentScene = Game::GetInstance().sceneManager->GetNextScene();
	if (currentScene.find("level_01") != std::string::npos) {
		GoToScene("level_02");
	} else if (currentScene.find("level_02") != std::string::npos) {
		GoToScene("level_03");
	} else {
		GoToScene("main_menu");
	}
}

#endif // !LUABINDING_HPP