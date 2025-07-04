/**
 * @file RenderSystem.hpp
 * @brief System for rendering sprites with transforms
 */

#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP
#include <SDL2/SDL.h>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderSystem
 * @brief System responsible for rendering sprites with position, rotation, and scaling
 * 
 * This system handles the rendering of all entities that have both SpriteComponent
 * and TransformComponent. It applies transformations including position, rotation,
 * scaling, and horizontal flipping based on the entity's components.
 */
class RenderSystem : public System {
public:
    /**
     * @brief Constructor for RenderSystem
     * 
     * Initializes the render system and sets up the required component types.
     * Only entities with both SpriteComponent and TransformComponent will be
     * processed by this system.
     */
    RenderSystem() {
        RequiredComponent<SpriteComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Renders all sprites with their transforms applied
     * 
     * Iterates through all entities with the required components and renders
     * their sprites using SDL. The rendering takes into account the camera
     * position, entity transforms (position, rotation, scale), and sprite
     * properties (source rectangle, flipping).
     * 
     * @param renderer SDL renderer used for drawing operations
     * @param AssetManager Asset manager containing loaded textures
     * @param camera Camera rectangle used for viewport calculations
     */
    void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetManager>& AssetManager, SDL_Rect& camera) {
        for (auto entity : GetSystemEntiities()) {
            const auto sprite = entity.GetComponent<SpriteComponent>();
            const auto transform = entity.GetComponent<TransformComponent>();
            
            // Source rectangle from sprite sheet
            SDL_Rect srcRect = sprite.srcRect;
            
            // Destination rectangle with camera offset and scaling applied
            SDL_Rect dstRect = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y),
                static_cast<int>(sprite.width * transform.scale.x),
                static_cast<int>(sprite.height * transform.scale.y),
            };
            
            // Render sprite with rotation and optional horizontal flip
            SDL_RenderCopyEx(
                renderer,
                AssetManager->GetTexture(sprite.textureId),
                &srcRect,
                &dstRect,
                transform.rotation,
                NULL,
                (sprite.flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
            );
        }
    }
};
#endif // RENDERSYSTEM_HPP