/**
 * @file AnimationComponent.hpp
 * @brief Component for managing sprite animations in the ECS system
 */

#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

/**
 * @struct AnimationComponent
 * @brief Component that handles sprite animation state and timing
 * 
 * This component manages the playback of sprite animations by tracking frame progression,
 * timing, and loop behavior. It works in conjunction with SpriteComponent to animate
 * entities in the game world.
 */
struct AnimationComponent {
    int numFrames;       ///< Total number of frames in the animation sequence
    int currentFrame;    ///< Current frame being displayed (1-based indexing)
    int frameSpeedRate;  ///< Speed multiplier for frame transitions (higher = faster)
    bool isLoop;         ///< Whether the animation should loop continuously when it reaches the end
    int startTime;       ///< SDL timestamp when the animation started (used for timing calculations)
    
    /**
     * @brief Constructor for AnimationComponent
     * @param numFrames Total number of frames in the animation (default: 1)
     * @param frameSpeedRate Speed multiplier for frame transitions (default: 1)
     * @param isLoop Whether the animation should loop continuously (default: true)
     * 
     * The constructor initializes the animation state with the current frame set to 1
     * and records the start time using SDL_GetTicks() for proper timing calculations.
     */
    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool isLoop = true) {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->startTime = SDL_GetTicks();
    }
};

#endif // !ANIMATIONCOMPONENT_HPP