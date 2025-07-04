/**
 * @file RenderTextSystem.hpp
 * @brief System for rendering text using SDL_ttf
 */

#ifndef RENDERTEXTSYSTEM_HPP
#define RENDERTEXTSYSTEM_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TextComponent.hpp"

/**
 * @class RenderTextSystem
 * @brief System responsible for rendering text entities on screen
 * 
 * This system handles the rendering of all entities that have both TextComponent
 * and TransformComponent. It uses SDL_ttf to render text into textures and
 * applies transformations including position and scaling. The text is rendered
 * with antialiasing using TTF_RenderText_Blended.
 */
class RenderTextSystem : public System {
public:
    /**
     * @brief Constructor for RenderTextSystem
     * 
     * Initializes the text render system and sets up the required component types.
     * Only entities with both TextComponent and TransformComponent will be
     * processed by this system.
     */
    RenderTextSystem() {
        RequiredComponent<TextComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Renders all text entities with their transforms applied
     * 
     * Iterates through all entities with the required components and renders
     * their text using SDL_ttf. The process involves creating a surface from
     * the text, converting it to a texture, and rendering it with camera offset
     * and scaling applied. Each text texture is created and destroyed per frame.
     * 
     * @param renderer SDL renderer used for drawing operations
     * @param assetManager Asset manager containing loaded fonts
     * @param camera Camera rectangle used for viewport calculations
     */
    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& assetManager, SDL_Rect& camera) {
        for (auto entity : GetSystemEntiities()) {
            auto& text = entity.GetComponent<TextComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            
            // Create surface from text with antialiasing
            SDL_Surface* surface = TTF_RenderText_Blended(assetManager->GetFont(text.fontId), text.text.c_str(), text.textColor);
            
            // Update text component dimensions based on rendered text
            text.width = surface->w;
            text.height = surface->h;
            
            // Convert surface to texture for rendering
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            
            // Calculate destination rectangle with camera offset and scaling
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y),
                text.width * static_cast<int>(transform.scale.x),
                text.height* static_cast<int>(transform.scale.y)
            };
            
            // Render text texture to screen
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            
            // Clean up texture resources
            SDL_DestroyTexture(texture);
        }
    }
    
private:
};
#endif // !RENDERTEXTSYSTEM_HPP