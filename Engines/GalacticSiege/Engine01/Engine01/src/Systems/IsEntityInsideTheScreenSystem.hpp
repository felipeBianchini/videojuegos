#ifndef ISENTITYINSIDETHESCREENSYSTEM_HPP
#define ISENTITYINSIDETHESCREENSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/IsEntityInsideTheScreenComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @class IsEntityInsideTheScreenSystem
 * @brief A system for determining if entities are fully within the screen boundaries in an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with IsEntityInsideTheScreenComponent, TransformComponent, and SpriteComponent.
 * It checks whether an entity's position and dimensions place it entirely within the screen boundaries
 * and updates the IsEntityInsideTheScreenComponent accordingly.
 */
class IsEntityInsideTheScreenSystem : public System {
public:
    /**
     * @brief Constructor for the IsEntityInsideTheScreenSystem.
     *
     * Initializes the system and specifies that entities must have IsEntityInsideTheScreenComponent,
     * TransformComponent, and SpriteComponent to be managed.
     */
    IsEntityInsideTheScreenSystem() {
        RequiredComponent<IsEntityInsideTheScreenComponent>();
        RequiredComponent<TransformComponent>();
        RequiredComponent<SpriteComponent>();
    }
    /**
     * @brief Updates the screen presence status of managed entities.
     *
     * Iterates through entities, calculates their bounding box based on position and sprite dimensions,
     * and determines if they are fully within the screen boundaries. Updates the
     * IsEntityInsideTheScreenComponent's flag accordingly.
     *
     * @param windowWidth The width of the game window.
     * @param windowHeight The height of the game window.
     */
    void Update(int windowWidth, int windowHeight) {
        for (auto entity : GetSystemEntiities()) {
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& insideComponent = entity.GetComponent<IsEntityInsideTheScreenComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            double posX = transform.position.x + sprite.width * transform.scale.x;
            double posY = transform.position.y + sprite.height * transform.scale.y;
            double w = static_cast<double>(windowWidth);
            double h = static_cast<double>(windowHeight);
            bool fullyInside = posX - (sprite.width / 2) > 0 && posY - (sprite.height / 2) > 0 && posX < w && posY < h;
            if (fullyInside) {
                insideComponent.isEntityInsideTheScreen = true;
            }
        }
    }

};

#endif // ISENTITYINSIDETHESCREENSYSTEM_HPP
