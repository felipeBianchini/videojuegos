#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TextComponent.hpp"

/**
 * @class RenderTextSystem
 * @brief A system for rendering text components within an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with TextComponent and TransformComponent, rendering text to the screen
 * using SDL and SDL_ttf libraries. It utilizes an AssetManager to access fonts and applies transformations
 * for positioning and scaling.
 */
class RenderTextSystem : public System {
public:
	/**
	 * @brief Constructor for the RenderTextSystem.
	 *
	 * Initializes the system and specifies that entities must have TextComponent and TransformComponent
	 * to be managed.
	 */
	RenderTextSystem() {
		RequiredComponent<TextComponent>();
		RequiredComponent<TransformComponent>();
	}
	/**
	 * @brief Updates and renders text for all managed entities.
	 *
	 * Iterates through entities, retrieves their text and transform components, and renders the text
	 * to the provided SDL renderer using the specified font and transformations from the AssetManager.
	 *
	 * @param renderer The SDL renderer used to draw the text.
	 * @param assetManager A unique pointer to the AssetManager for accessing fonts.
	 */
	void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& assetManager) {
		for (auto entity : GetSystemEntiities()) {
			auto& text = entity.GetComponent<TextComponent>();
			auto& transform = entity.GetComponent<TransformComponent>();
			SDL_Surface* surface = TTF_RenderText_Blended(assetManager->GetFont(text.fontId), text.text.c_str(), text.textColor);
			text.width = surface->w;
			text.height = surface->h;
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				text.width * static_cast<int>(transform.scale.x),
				text.height* static_cast<int>(transform.scale.y)
			};
			SDL_RenderCopy(renderer, texture, NULL, &dstRect);
			SDL_DestroyTexture(texture);
		}
	}
private:
};

#endif // !RENDERTEXTSYSTEM_HPP