#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include <SDL.h>

#include <string>

/**
 * @brief Component representing a sprite for rendering.
 *
 * Holds the texture identifier, dimensions, and source rectangle for sprite extraction.
 */
struct SpriteComponent {
	std::string textureId; ///< Identifier of the texture used by the sprite.
	int width;             ///< Width of the sprite in pixels.
	int height;            ///< Height of the sprite in pixels.
	SDL_Rect srcRect;      ///< Source rectangle defining the portion of the texture to render.

	/**
	 * @brief Constructs a SpriteComponent with optional parameters.
	 *
	 * @param textureId The texture ID to use. Defaults to "none".
	 * @param width Width of the sprite in pixels. Default is 0.
	 * @param height Height of the sprite in pixels. Default is 0.
	 * @param srcRectX X coordinate of the source rectangle within the texture. Default is 0.
	 * @param srcRectY Y coordinate of the source rectangle within the texture. Default is 0.
	 */
	SpriteComponent(const std::string& textureId = "none", int width = 0,
		int height = 0, int srcRectX = 0, int srcRectY = 0) {
		this->textureId = textureId;
		this->width = width;
		this->height = height;
		this->srcRect = {srcRectX, srcRectY, width, height};

	}
};

#endif // SPRITECOMPONENT_HPP