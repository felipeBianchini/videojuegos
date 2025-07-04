/**
 * @file AnimationSystem.hpp
 * @brief ECS system for handling sprite animations
 */

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP
#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

/**
 * @class AnimationSystem
 * @brief ECS system responsible for updating sprite animations
 * 
 * The AnimationSystem manages the animation of sprite entities by updating
 * their current animation frame based on elapsed time and frame rate.
 * It works with entities that have both AnimationComponent and SpriteComponent,
 * calculating the appropriate frame to display and updating the sprite's
 * source rectangle accordingly.
 */
class AnimationSystem : public System {
public:
    /**
     * @brief Constructor for AnimationSystem
     * 
     * Initializes the animation system and specifies the required components.
     * Entities must have both AnimationComponent and SpriteComponent to be
     * processed by this system.
     */
    AnimationSystem() {
        RequiredComponent<AnimationComponent>();
        RequiredComponent<SpriteComponent>();
    }
    
    /**
     * @brief Updates all animated entities in the system
     * 
     * Iterates through all entities with animation and sprite components,
     * calculates the current animation frame based on elapsed time and
     * frame rate, then updates the sprite's source rectangle to display
     * the correct frame. The animation loops automatically when reaching
     * the end of the frame sequence.
     * 
     * Frame calculation uses the formula:
     * currentFrame = ((currentTime - startTime) * frameRate / 1000) % numFrames
     * 
     * The sprite's source rectangle x-coordinate is updated to:
     * srcRect.x = currentFrame * spriteWidth
     */
    void Update() {
        for (auto entity : GetSystemEntiities()) {
            auto& animation = entity.GetComponent<AnimationComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            
            animation.currentFrame = ((SDL_GetTicks() - animation.startTime)
                * animation.frameSpeedRate / 1000) % animation.numFrames;
            sprite.srcRect.x = animation.currentFrame * sprite.width;
        }
    }
};

#endif // !ANIMATIONSYSTEM_HPP