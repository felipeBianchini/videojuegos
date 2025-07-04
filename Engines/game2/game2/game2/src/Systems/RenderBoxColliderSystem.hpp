/**
 * @file RenderBoxColliderSystem.hpp
 * @brief System for rendering box collider debug visualization
 */

#ifndef RENDERBOXCOLLIDERSYSTEM_HPP
#define RENDERBOXCOLLIDERSYSTEM_HPP
#include <SDL2/SDL.h>
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class RenderBoxColliderSystem
 * @brief System responsible for rendering box collider bounds as debug visualization
 * 
 * This system renders the bounding boxes of all entities that have both
 * BoxColliderComponent and TransformComponent. The colliders are drawn as
 * red rectangles on screen for debugging purposes.
 */
class RenderBoxColliderSystem : public System {
public:
    /**
     * @brief Constructor for RenderBoxColliderSystem
     * 
     * Initializes the render system and sets up the required component types.
     * Only entities with both BoxColliderComponent and TransformComponent
     * will be processed by this system.
     */
    RenderBoxColliderSystem() {
        RequiredComponent<BoxColliderComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Renders box collider bounds for all entities in the system
     * 
     * Iterates through all entities with the required components and draws
     * their collision bounds as red rectangles. The rendering takes into
     * account the camera position and entity transforms.
     * 
     * @param renderer SDL renderer used for drawing operations
     * @param camera Camera rectangle used for viewport calculations
     */
    void Update(SDL_Renderer* renderer, SDL_Rect& camera) {
        for (auto entity : GetSystemEntiities()) {
            const auto& collider = entity.GetComponent<BoxColliderComponent>();
            const auto& transform = entity.GetComponent<TransformComponent>();
            
            // Calculate screen position relative to camera
            SDL_Rect box = {
                static_cast<int>(transform.position.x - camera.x),
                static_cast<int>(transform.position.y - camera.y),
                static_cast<int>(collider.width * transform.scale.x),
                static_cast<int>(collider.heigth * transform.scale.y)
            };
            
            // Draw collider bounds in red
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &box);
        }
    }
};
#endif // !RENDERBOXCOLLIDERSYSTEM_HPP