/**
 * @file CameraMovementSystem.hpp
 * @brief ECS system for handling camera following behavior
 */

#ifndef CAMERAMOVEMENTSYSTEM_HPP
#define CAMERAMOVEMENTSYSTEM_HPP
#include <SDL2/SDL.h>
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

/**
 * @class CameraMovementSystem
 * @brief ECS system responsible for managing camera following behavior
 * 
 * The CameraMovementSystem handles camera movement by making the camera follow
 * entities that have a CameraFollowComponent. The system centers the camera
 * on the followed entity while ensuring the camera stays within the map boundaries.
 * It processes entities with both CameraFollowComponent and TransformComponent.
 */
class CameraMovementSystem : public System {
public:
    /**
     * @brief Constructor for CameraMovementSystem
     * 
     * Initializes the camera movement system and specifies the required components.
     * Entities must have both CameraFollowComponent and TransformComponent to be
     * processed by this system for camera following behavior.
     */
    CameraMovementSystem() {
        RequiredComponent<CameraFollowComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Updates the camera position to follow entities
     * @param camera Reference to the SDL_Rect representing the camera viewport
     * 
     * Updates the camera position to follow entities with CameraFollowComponent.
     * The camera is centered on the entity's position while respecting map boundaries:
     * 
     * 1. Horizontally centers the camera on the entity if the entity is not too close
     *    to the right edge of the map (within half camera width)
     * 2. Vertically centers the camera on the entity if the entity is not too close
     *    to the bottom edge of the map (within half camera height)
     * 3. Clamps the camera position to prevent it from going outside the map bounds
     *    (ensures camera.x >= 0 and camera.y >= 0)
     * 
     * The camera positioning formula:
     * - camera.x = entity.x - (camera.width / 2)
     * - camera.y = entity.y - (camera.height / 2)
     * 
     * Boundary checks prevent the camera from showing areas outside the map.
     */
    void Update(SDL_Rect& camera) {
        for (auto entity : GetSystemEntiities()) {
            const auto& transform = entity.GetComponent<TransformComponent>();
            
            if (transform.position.x + (camera.w / 2) <
                static_cast<float>(Game::GetInstance().mapWidth)) {
                camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
            }
            
            if (transform.position.y + (camera.h / 2) <
                static_cast<float>(Game::GetInstance().mapHeigth)) {
                camera.y = static_cast<int>(transform.position.y) - (camera.h / 2);
            }
            
            camera.x = camera.x < 0 ? 0 : camera.x;
            camera.y = camera.y < 0 ? 0 : camera.y;
        }
    }
};

#endif // !CAMERAMOVEMENTSYSTEM_HPP