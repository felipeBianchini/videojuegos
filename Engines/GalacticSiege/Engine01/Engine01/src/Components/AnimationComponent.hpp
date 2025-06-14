#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <glm/glm.hpp>
#include <SDL.h>

/**
 * @brief Component that handles sprite animation details.
 *
 * Stores animation frame count, current frame, animation speed, looping flag, and start time.
 */
struct AnimationComponent {
	int numFrames;       ///< Total number of frames in the animation.
	int currentFrame;    ///< Current frame being displayed.
	int frameSpeedRate;  ///< Speed rate of frame progression (lower is faster).
	bool isLoop;         ///< Whether the animation should loop.
	int startTime;       ///< Time (in milliseconds) when the animation started.

	/**
	 * @brief Construct a new AnimationComponent object.
	 *
	 * @param numFrames Total frames in the animation (default 1).
	 * @param frameSpeedRate Speed of frame update (default 1).
	 * @param isLoop Should the animation loop? (default true).
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