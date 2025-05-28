#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"

/**
 * @class AnimationSystem
 * @brief A system for managing sprite animations within an Entity-Component-System (ECS) architecture.
 *
 * This system handles entities with AnimationComponent and SpriteComponent, updating their sprite frames
 * based on animation timing. It also manages the lifecycle of certain animated entities (e.g., explosions)
 * by marking them for deletion when their animation completes.
 */
class AnimationSystem : public System {
public:
    /**
     * @brief Constructor for the AnimationSystem.
     *
     * Initializes the system and specifies that entities must have AnimationComponent and SpriteComponent
     * to be managed.
     */
	AnimationSystem() {
		RequiredComponent<AnimationComponent>();
		RequiredComponent<SpriteComponent>();
	}
    /**
     * @brief Updates the animation state of managed entities.
     *
     * Iterates through entities, calculates the current animation frame based on elapsed time, and updates
     * the sprite's source rectangle. Marks entities of type 12 (e.g., explosions) for deletion when their
     * animation completes.
     */
    void Update() {
        for (auto entity : GetSystemEntiities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();

            int elapsedFrames = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000);
            if (elapsedFrames >= animation.numFrames) {
                if (entity.HasComponent<EntityTypeComponent>()) {
                    int type = entity.GetComponent<EntityTypeComponent>().entityType;
                    if (type == 12) {
                        entity.Kill();
                        continue;
                    }
                }
            }
            else {
                animation.currentFrame = elapsedFrames;
                sprite.srcRect.x = animation.currentFrame * sprite.width;
            }
        }
    }

};

#endif // !ANIMATIONSYSTEM_HPP