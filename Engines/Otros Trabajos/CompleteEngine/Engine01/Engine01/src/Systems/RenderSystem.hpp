#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class RenderSystem : public System {
public:
	RenderSystem() {
		RequiredComponent<SpriteComponent>();
		RequiredComponent<TransformComponent>();
	}
	void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& AssetManager, SDL_Rect& camera) {
		for (auto entity : GetSystemEntiities()) {
			const auto sprite = entity.GetComponent<SpriteComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			SDL_Rect srcRect = sprite.srcRect;
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x - camera.x),
				static_cast<int>(transform.position.y - camera.y),
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