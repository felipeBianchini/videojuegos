#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderSystem
 * @brief A system for rendering sprites within an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with SpriteComponent and TransformComponent, rendering sprites to the screen
 * using SDL. It utilizes an AssetManager to access textures and applies transformations for positioning,
 * scaling, and rotation.
 */
class RenderSystem : public System {
public:
	/**
	 * @brief Constructor for the RenderSystem.
	 *
	 * Initializes the system and specifies that entities must have SpriteComponent and TransformComponent
	 * to be managed.
	 */
	RenderSystem() {
		RequiredComponent<SpriteComponent>();
		RequiredComponent<TransformComponent>();
	}
	/**
	 * @brief Updates and renders sprites for all managed entities.
	 *
	 * Iterates through entities, retrieves their sprite and transform components, and renders the sprites
	 * to the provided SDL renderer using the specified texture and transformations from the AssetManager.
	 *
	 * @param renderer The SDL renderer used to draw the sprites.
	 * @param assetManager A unique pointer to the AssetManager for accessing textures.
	 */
	void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& AssetManager) {
		for (auto entity : GetSystemEntiities()) {
			const auto sprite = entity.GetComponent<SpriteComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y),
			};
			SDL_RenderCopyEx(
				renderer,
				AssetManager->GetTexture(sprite.textureId),
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				SDL_FLIP_NONE
			);
		}
	}
};

#endif RENDERSYSTEM_HPP